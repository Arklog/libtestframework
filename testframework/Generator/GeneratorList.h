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

	template <size_t... I>
	void generate_index_max(std::integer_sequence<size_t, I...>);

	template <size_t... I>
	void generate_next(std::integer_sequence<size_t, I...>);

	template <size_t... I>
	void generate_at(size_t i, std::integer_sequence<size_t, I...>);

	template <size_t... I>
	void make_current(std::integer_sequence<size_t, I...>);

	template <size_t... I>
	void delete_tuple(std::integer_sequence<size_t, I...>);

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
	this->finished = false;
	this->list = std::make_tuple(args...);
	this->index_current = 0;
	using ttype = decltype(this->list);
	this->make_current(std::make_index_sequence<std::tuple_size_v<ttype>>{});
	this->generate_index_max(
		std::make_index_sequence<std::tuple_size_v<ttype>>{});
}

template <typename... T> GeneratorList<T...>::~GeneratorList() {
	this->delete_tuple(
		std::make_index_sequence<std::tuple_size_v<decltype(this->list)>>{});
}

template <typename... T>
std::tuple<T...> GeneratorList<T...>::get_current() const {
	return this->current;
}

template <typename... T> std::tuple<T...> GeneratorList<T...>::get_next() {
	this->generate_next(
		std::make_index_sequence<std::tuple_size_v<decltype(this->list)>>{});
	return this->get_current();
}

template <typename... T>
std::tuple<T...> GeneratorList<T...>::get_at(size_t i) {
	this->generate_at(
		i, std::make_index_sequence<std::tuple_size_v<decltype(this->list)>>{});
	return this->get_current();
}

template <typename... T> std::size_t GeneratorList<T...>::get_index() const {
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
template <std::size_t... I>
void GeneratorList<T...>::generate_index_max(
	std::integer_sequence<size_t, I...>) {
	size_t max;
	max = 1;

	((max *= std::get<I>(this->list)->get_index_max() + 1), ...);
	this->index_max = max - 1;
}

template <typename... T>
template <size_t... I>
void GeneratorList<T...>::generate_next(std::integer_sequence<size_t, I...> i) {
	if (this->get_index() >= this->get_index_max())
		return;
	this->generate_at(++this->index_current, i);
}

template <typename... T>
template <size_t... I>
void GeneratorList<T...>::generate_at(size_t i,
									  std::integer_sequence<size_t, I...> s) {
	(([this, &i]() {
		 auto gen = std::get<I>(this->list);
		 gen->generate_at(i % (gen->get_index_max() + 1));
		 i /= gen->get_index_max() + 1;
	 }()),
	 ...);
	this->make_current(s);
}

template <typename... T>
template <size_t... I>
void GeneratorList<T...>::make_current(std::integer_sequence<size_t, I...>) {
	((std::get<I>(this->current) = std::get<I>(this->list)->get_current()),
	 ...);
}

template <typename... T>
template <size_t... I>
void GeneratorList<T...>::delete_tuple(std::integer_sequence<size_t, I...>) {
	((delete std::get<I>(this->list)), ...);
}

#endif
