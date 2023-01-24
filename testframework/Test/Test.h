#ifndef TEST_H
#define TEST

#include "testframework/Generator/GeneratorList.h"
#include <functional>

template <typename... T> class Test {
  private:
	std::function<bool(T...)> _f;
	GeneratorList<T...> list;
	bool result;

  public:
	Test(std::function<bool(T...)> f, GeneratorList<T...> list);
	~Test();

	bool run_one();
	bool run_all();
	bool is_finished() const;
};

template <typename... T> bool Test<T...>::run_one() {
	if (this->is_finished())
		return;
	list.generate_next();
	this->result &= std::apply(this->_f, list.get_current());
	return this->result;
}

template <typename... T> bool Test<T...>::run_all() {
	while (!this->is_finished())
		this->run_one();
	return (this->result);
}

template <typename... T> bool Test<T...>::is_finished() const {
	return (!this->is_finished || this->list.is_finished());
}

#endif