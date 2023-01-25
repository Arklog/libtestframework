#ifndef TEST_H
#define TEST_H

#include "testframework/Generator/GeneratorList.h"
#include "testframework/Test/TestBase.h"
#include <functional>
#include <tuple>

template <typename... T> class Test : public TestBase {
  private:
	std::function<bool(T...)> _f;
	GeneratorList<T...> list;

  public:
	Test(std::function<bool(T...)> f, GeneratorList<T...> list);
	~Test();

	bool run_one();
	bool run_all();
};

template <typename... T> bool Test<T...>::run_one() {
	this->result &= std::apply(this->_f, list.get_current());
	if (!list.is_finished())
		list.generate_next();
	else
		this->finished = true;
	return this->result;
}

template <typename... T> bool Test<T...>::run_all() {
	while (!this->is_finished())
		this->run_one();
	return (this->result);
}

#endif