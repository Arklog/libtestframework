#ifndef GENERATOR_LIST_H
#define GENERATOR_LIST_H

#include "testframework/Generator/Generator.h"
#include <tuple>

template <typename... T> class GeneratorList {
  private:
	std::tuple<Generator<T> *...> list;
	std::tuple<T...> current;


	size_t index_current;
	size_t index_max;

	bool finished;

	template <size_t... I> void generate_next();
	template <size_t... I> void generate_at(size_t i);

  public:
	GeneratorList(Generator<T> *...args);
	~GeneratorList();

	std::tuple<T...> get_current() const;
	std::tuple<T...> get_next();
	std::tuple<T...> get_at(size_t i);

	std::size_t get_index() const;
	std::size_t get_index_max() const;

	bool is_finished() const;
};

template <typename... T>
GeneratorList<T...>::GeneratorList(Generator<T> *...args) {
	this->list = std::make_tuple(args...);
}

template <typename... T> GeneratorList<T...>::~GeneratorList() {}

template <typename... T>
std::tuple<T...> GeneratorList<T...>::get_current() const {
	return this->list;
}

template <typename... T> std::tuple<T...> GeneratorList<T...>::get_next() {
	this->generate_next<std::tuple_size_v<this->list>>();
	return this->get_current();
}

template <typename... T>
std::tuple<T...> GeneratorList<T...>::get_at(size_t i) {
	this->generate_at<std::tuple_size_v<this->list>>(i);
}

template <typename... T>
std::size_t GeneratorList<T...>::get_index() const {
	return this->index_current;
}

template <typename... T>
std::size_t GeneratorList<T...>::get_index_max() const {
	return this->index_max;
}

template <typename... T> bool GeneratorList<T...>::is_finished() const {
	return (this->get_index() >= this->get_index_max());
}

template <typename... T>
template <size_t... I>
void GeneratorList<T...>::generate_next() {
	if (this->index_current > this->index_max)
		return ;
}

#endif
