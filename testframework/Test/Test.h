#ifndef TEST_H
#define TEST_H

#include <functional>
#include <iostream>
#include <tuple>

#include "testframework/Generator/GeneratorList.h"
#include "testframework/Global/mutex.h"
#include "testframework/Socket/Client.h"
#include "testframework/Test/TestBase.h"
#include "testframework/testframework/TestFramework.h"

template <typename... T> class Test : public TestBase {
  private:
	std::function<bool(T...)> _f;
	GeneratorList<T...> *list;

	static std::function<void(Test<T...> *, bool, size_t,
							  std::vector<std::tuple<size_t, std::string>>)>
		callback_run_one;

	template <size_t... I>
	std::vector<std::tuple<size_t, std::string>>
		_gen_db_args(std::tuple<T...>, std::integer_sequence<size_t, I...>);

  protected:
	virtual bool _run_one() override;
	virtual bool _run_all() override;

  public:
	Test(std::string name, std::function<bool(T...)> f,
		 GeneratorList<T...> *list);
	~Test();

	virtual size_t get_test_numbers() const override;
};

template <typename... T>
std::function<void(Test<T...> *, bool, size_t,
				   std::vector<std::tuple<size_t, std::string>>)>
	Test<T...>::callback_run_one =
		[](Test<T...> *t, bool r, size_t i,
		   std::vector<std::tuple<size_t, std::string>> tuple) {
			std::string str[SOCKET_NARGS];

			for (size_t i = 0; i < tuple.size(); ++i)
				str[i] = std::get<1>(tuple.at(i));

			TestFramework::get_instance()->get_client_socket()->send(
				t->get_id(), t->get_name(), str, i, tuple.size(), r);
		};

template <typename... T>
Test<T...>::Test(std::string name, std::function<bool(T...)> f,
				 GeneratorList<T...> *list)
	: TestBase(name), _f(f), list(list) {}

template <typename... T> Test<T...>::~Test() { delete this->list; }

template <typename... T> bool Test<T...>::_run_one() {
	bool r;

#ifdef DEBUG
	cout_mutex.lock();
	std::cout << "[INFO]: " << this->get_name() << " running "
			  << list->get_index() << std::endl;
	cout_mutex.unlock();
#endif
	r = std::apply(this->_f, list->get_current());
	this->callback_run_one(
		this, r, this->list->get_index(),
		this->_gen_db_args(
			this->list->get_current(),
			std::make_index_sequence<
				std::tuple_size_v<decltype(this->list->get_current())>>{}));
	if (!list->is_finished())
		list->get_next();
	else
		this->finished = true;
	return this->result;
}

template <typename... T> bool Test<T...>::_run_all() {
#ifdef DEBUG
	cout_mutex.lock();
	std::cout << "[INFO]: running all tests for " << this->get_name()
			  << std::endl;
	cout_mutex.unlock();
#endif

	while (!this->is_finished())
		this->run_one();
	return (this->result);
}

template <typename... T>
template <size_t... I>
std::vector<std::tuple<size_t, std::string>>
Test<T...>::_gen_db_args(std::tuple<T...> t,
						 std::integer_sequence<size_t, I...>) {
	std::vector<std::tuple<size_t, std::string>> vec;
	((vec.push_back(std::make_tuple(I, std::to_string(std::get<I>(t))))), ...);
	return vec;
}

template <typename... T> size_t Test<T...>::get_test_numbers() const {
	return this->list->get_index_max() + 1;
}

#endif