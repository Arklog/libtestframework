#ifndef TEST_H
#define TEST_H

#include "testframework/Generator/GeneratorList.h"
#include "testframework/Test/TestBase.h"
#include "testframework/testframework/TestFramework.h"
#include <functional>
#include <tuple>

template <typename... T> class Test : public TestBase {
  private:
	std::function<bool(T...)> _f;
	GeneratorList<T...> list;

	static std::function<void(Test<T...> *,bool, size_t,
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
		 GeneratorList<T...> list);
	~Test();
};

template <typename... T>
std::function<void(Test<T...> *, bool, size_t, std::vector<std::tuple<size_t, std::string>>)>
	Test<T...>::callback_run_one =
		[](Test *test, bool r, size_t i,
		   std::vector<std::tuple<size_t, std::string>> t) {
			TestFramework::get_instance()->get_database()->add_result(
				test->get_name(), i, r, t);
		};

template <typename... T>
Test<T...>::Test(std::string name, std::function<bool(T...)> f,
				 GeneratorList<T...> list)
	: TestBase(name), _f(f), list(list) {}

template <typename... T>
Test<T...>::~Test() {}

template <typename... T> bool Test<T...>::_run_one() {
	bool r;

	r = std::apply(this->_f, list.get_current());
	this->callback_run_one(
		this, r, this->list.get_index(),
		this->_gen_db_args(
			this->list.get_current(),
			std::make_index_sequence<
				std::tuple_size_v<decltype(this->list.get_current())>>{}));
	if (!list.is_finished())
		list.get_next();
	else
		this->finished = true;
	return this->result;
}

template <typename... T> bool Test<T...>::_run_all() {
	while (!this->is_finished())
		this->run_one();
	return (this->result);
}

template <typename... T>
template <size_t... I>
std::vector<std::tuple<size_t, std::string>> Test<T...>::_gen_db_args(std::tuple<T...> t, std::integer_sequence<size_t, I...>)
{
	std::vector<std::tuple<size_t, std::string>> vec;
	((vec.push_back(std::make_tuple(I, std::to_string(std::get<I>(t))))),...);
	return vec;
}
#endif