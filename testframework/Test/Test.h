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

	/**
	 * Called when a test have been run, by default send test result to the
	 * server using the client
	 */
	static std::function<void(Test<T...> *, bool, size_t,
							  std::vector<std::tuple<size_t, std::string>>)>
		callback_run_one;

	template <size_t... I>
	std::vector<std::tuple<size_t, std::string>>
		_gen_db_args(std::tuple<T...>, std::integer_sequence<size_t, I...>);

  protected:
	bool _run_one() override;
	bool _run_all() override;

  public:
	Test(std::string name, std::function<bool(T...)> f,
		 GeneratorList<T...> *list);
	~Test() override;

	[[nodiscard]] size_t get_test_numbers() const override;

	void jump() override;
};

template <typename... T>
std::function<void(Test<T...> *, bool, size_t,
				   std::vector<std::tuple<size_t, std::string>>)>
	Test<T...>::callback_run_one = nullptr;
template <typename... T> void Test<T...>::jump() {
	if (!this->list->is_finished())
		this->list->get_next();
	else
		this->finished = true;
}

template <typename... T>
Test<T...>::Test(std::string name, std::function<bool(T...)> f,
				 GeneratorList<T...> *list)
	: TestBase(name), _f(f), list(list) {}

template <typename... T> Test<T...>::~Test() { delete this->list; }

template <typename... T> bool Test<T...>::_run_one() {
	bool r;

	print_info(get_name(), "running", list->get_index());

	r = std::apply(this->_f, list->get_current());
	auto args =
		_gen_db_args(list->get_current(),
					 std::make_index_sequence<
						 std::tuple_size_v<decltype(list->get_current())>>{});
	this->socket_data = t_socket_data(this, this->list->get_index(), r, args);
	if (!list->is_finished())
		list->get_next();
	else
		this->finished = true;
	return this->result;
}

template <typename... T> bool Test<T...>::_run_all() {
	print_info("running all tests for:", get_name());

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