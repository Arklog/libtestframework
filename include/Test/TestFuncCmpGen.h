#ifndef TESTFUNCCMPGEN_H
#define TESTFUNCCMPGEN_H

#include "Test.h"
#include "TestFuncCmp.h"

template <typename T>
class Generator;

template <typename RetType, typename... Types>
class TestFuncCmpGen : public Test
{
private:
	std::function<RetType(Types...)> _f1;
	std::function<RetType(Types...)> _f2;
	std::tuple<Generator<Types> *...> _args;

	TestFuncCmp<RetType, Types...> *_cmp;

	template <typename G, size_t N, size_t... I>
	void _iterate_args(Generator<G> *g, std::index_sequence<I...>);

public:
	TestFuncCmpGen<RetType, Types...>(std::function<RetType(Types...)> f1,
									  std::function<RetType(Types...)> f2,
									  Generator<Types> *...args);
	~TestFuncCmpGen();

	std::vector<std::string> to_string() const override;
	std::string get_error() const;
	void run();
};

template <typename RetType, typename... Types>
TestFuncCmpGen<RetType, Types...>::TestFuncCmpGen(
	std::function<RetType(Types...)> f1,
	std::function<RetType(Types...)> f2,
	Generator<Types> *...args) : _f1(f1), _f2(f2), _cmp(nullptr)
{
	this->_args = std::make_tuple(args...);
}

template <typename RetType, typename... Types>
TestFuncCmpGen<RetType, Types...>::~TestFuncCmpGen()
{
}

template <typename RetType, typename... Types>
std::vector<std::string> TestFuncCmpGen<RetType, Types...>::to_string() const
{
	std::vector<std::string> i = std::vector<std::string>();
	return i;
}

template <typename RetType, typename... Types>
std::string TestFuncCmpGen<RetType, Types...>::get_error() const
{
	return "";
}

template <typename T, typename... Types>
void TestFuncCmpGen<T, Types...>::run()
{
	auto	I = std::make_index_sequence<std::tuple_size<decltype(this->_args)>::value>();
	std::make_from_tuple
	std::tuple<Types...> tuple = std::make_tuple<Types...>(std::get<I>(this->_args)->generate()...);
}

#endif