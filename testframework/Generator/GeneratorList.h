#ifndef GENERATORLIST_H
#define GENERATORLIST_H

#ifdef DEBUG
#include <iostream>
#endif

#include <iostream>
#include <tuple>
#include "Generator/Generator.h"

template <typename... Types>
class GeneratorList
{
private:
	/**
	 * @brief List of generators
	 */
	std::tuple<Generator<Types>*...> _tuple;
	/**
	 * @brief Last tuple to have been generated
	 */
	std::tuple<Types...> _ctuple;
	/**
	 * @brief Maximum number of tuples
	 */
	std::size_t _ntuple;
	/**
	 * @brief Current tuple index
	 */
	std::size_t _index;

	/**
	 * @brief Delete the generators, is called in the dtor
	 * @return
	 */
	template <std::size_t... I>
	void _delete_generators(std::index_sequence<I...>);

	/**
	 * @brief Compute the maximum number of tuples to be generated
	 * @tparam ...I
	 * @param
	 */
	template <std::size_t... I>
	void _compute_tsize(std::index_sequence<I...>);

	/**
	 * @brief Generate the tuple at nth index
	 * @tparam N
	 * @tparam ...I
	 * @param index
	 * @param
	 */
	template <std::size_t N, std::size_t... I>
	void _gen_tuple(std::size_t index, std::index_sequence<I...>);

public:
	GeneratorList<Types...>(Generator<Types> *...);
	~GeneratorList();

	/**
	 * @brief Return the maximum numbers of tuple to be generated.
	 * @tparam ...Types
	 */
	std::size_t get_max() const;

	/**
	 * @brief Return the index of the last tuple to have been generated
	 * @tparam ...Types
	 * @param
	 */
	std::size_t get_current() const;

	/**
	 * @brief Get the nth tuple in the list
	 * @tparam ...Types
	 */
	std::tuple<Types...> get_nth(std::size_t i);

	/**
	 * @brief Generate the next tuple, if the current one is
	 * allready the last one, it will be returned again.
	 * @tparam ...Types
	 */
	std::tuple<Types...> get_next();
};

template <typename... Types>
GeneratorList<Types...>::GeneratorList(Generator<Types> *...args)
{
	using tsize = std::tuple_size<decltype(this->_tuple)>;

	this->_tuple = std::make_tuple(args...);
	this->_compute_tsize(std::make_index_sequence<tsize::value>());
	this->_index = 0;
	this->_ctuple = this->get_nth(0);
}

template <typename... Types>
GeneratorList<Types...>::~GeneratorList()
{
	this->_delete_generators(std::make_index_sequence<std::tuple_size<decltype(this->_tuple)>::value>());
}

template <typename... Types>
template <std::size_t... I>
void GeneratorList<Types...>::_delete_generators(std::index_sequence<I...>)
{
	#ifdef DEBUG
	std::cout << "deleting GeneratorList" << std::endl;
	#endif
	(delete std::get<I>(this->_tuple), ...);
}

template <typename... Types>
template <std::size_t... I>
void GeneratorList<Types...>::_compute_tsize(std::index_sequence<I...>)
{
	std::size_t i;

	i = 1;
	((i *= std::get<I>(this->_tuple)->size()), ...);
	this->_ntuple = i;
}

template <typename... Types>
std::size_t GeneratorList<Types...>::get_max() const
{
	return this->_ntuple;
}

template <typename... Types>
std::size_t GeneratorList<Types...>::get_current() const
{
	return this->_index;
}

template <typename... Types>
std::tuple<Types...> GeneratorList<Types...>::get_nth(std::size_t i)
{
	using n = typename std::tuple_size<decltype(this->_tuple)>;
	this->_gen_tuple<n::value>(i, std::make_index_sequence<n::value>());
	return this->_ctuple;
}

template <typename... Types>
std::tuple<Types...> GeneratorList<Types...>::get_next()
{
	return (this->get_nth(++(this->_index)));
}

template <typename... Types>
template <std::size_t N, std::size_t... I>
void GeneratorList<Types...>::_gen_tuple(std::size_t index, std::index_sequence<I...>)
{
	(([&index, this]()
	  {
		auto g = std::get<N - I - 1>(this->_tuple);
		#ifdef DEBUG
		std::cout << (void *)g << std::endl;
		#endif
		std::size_t incr = index % g->size();
		g->get_nth(incr);
		index /= g->size(); })(),
	 ...);
	this->_ctuple = std::make_tuple(std::get<I>(this->_tuple)->value()...);
	(std::get<I>(this->_tuple)->reset(), ...);
}

#endif