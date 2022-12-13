#ifndef TESTFUNCCMPGEN_H
#define TESTFUNCCMPGEN_H

#include "Test.h"
#include "TestFuncCmp.h"
#include "Generator.h"

/// @brief This class test two function return value unsing a generator 
/// @tparam RetType Return type of the functions
/// @tparam ...Types Argument types for the functions
template <typename RetType, typename... Types>
class TestFuncCmpGen : public Test
{
private:
	std::function<RetType(Types...)> _f1;
	std::function<RetType(Types...)> _f2;
	std::tuple<Generator<Types> *...> _args;

	TestFuncCmp<RetType, Types...> _cmp;

public:
	TestFuncCmpGen<RetType, Types...>(std::function<RetType(Types...)> f1,
										std::function<RetType(Types...)> f2,
										Generator<Types> *...args);
	~TestFuncCmpGen();

	std::vector<std::string> 	to_string() const override;
	std::string 				get_error() const override;
	bool 						executed() const override;
	bool 						result() const override;
	void 						run() override;
};

template <typename RetType, typename... Types>
TestFuncCmpGen<RetType, Types...>::TestFuncCmpGen(
	std::function<RetType(Types...)> f1,
	std::function<RetType(Types...)> f2,
	Generator<Types> *...args) : _f1(f1), _f2(f2)
{
	this->_args = std::make_tuple(args...);
}

template <typename RetType, typename... Types>
TestFuncCmpGen<RetType, Types...>::~TestFuncCmpGen()
{
}

template <typename RetType, typename... Types>
std::vector<std::string>	TestFuncCmpGen<RetType, Types...>::to_string() const
{
	std::vector<std::string>	i = std::vector<std::string>();
	return i;
}

template <typename RetType, typename... Types>
std::string	TestFuncCmpGen<RetType, Types...>::get_error() const
{
	return "";
}

template <typename RetType, typename... Types>
bool	TestFuncCmpGen<RetType, Types...>::executed() const
{

}

template <typename RetType, typename... Types>
bool TestFuncCmpGen<RetType, Types...>::result() const
{
	return false;
}

template <typename T, typename... Types>
void	TestFuncCmpGen<T, Types...>::run()
{
	return ;
}
#endif