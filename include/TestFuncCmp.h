#ifndef TESTFUNCCMP_H
#define TESTFUNCCMP_H

#include <functional>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <string>
#include "Test.h"

template <typename RetType, typename... Types>
class TestFuncCmp : public Test
{
private:
	std::function<RetType(Types...)> _f1;
	std::function<RetType(Types...)> _f2;
	std::tuple<Types...> _args;

	RetType _ret1;
	RetType _ret2;

public:
	TestFuncCmp<RetType, Types...>(std::function<RetType(Types...)> f1,
								   std::function<RetType(Types...)> f2,
								   Types... args);
	~TestFuncCmp();

	void run() override;
	std::string get_error() const override;
};

template <typename RetType, typename... Types>
TestFuncCmp<RetType, Types...>::TestFuncCmp(
	std::function<RetType(Types...)> f1,
	std::function<RetType(Types...)> f2,
	Types... args) : _f1(f1), _f2(f2)
{
	std::tuple<Types...> t = std::make_tuple(args...);
	this->_args = t;
}

template <typename RetType, typename... Types>
TestFuncCmp<RetType, Types...>::~TestFuncCmp()
{
}

template <typename RetType, typename... Types>
void TestFuncCmp<RetType, Types...>::run()
{
	this->_ret1 = std::apply(this->_f1, this->_args);
	this->_ret2 = std::apply(this->_f2, this->_args);
	this->_exec = true;
	this->_result = this->_ret1 == this->_ret2;
}

template <typename T>
std::string toString(T i)
{
	return (std::to_string(i));
}

template <>
std::string toString<const char *>(const char *i)
{
	return (std::string(i));
}

template <typename Tuple, std::size_t... I>
std::string tuple_to_str(Tuple t, std::index_sequence<I...>)
{
	std::string r;
	(([&r, t]()
	  {
		using TYPE = typename std::tuple_element<I, decltype(t)>::type;
		r.append(toString<TYPE>(std::get<I>(t)));
		r.append(", "); })(),
	 ...);
	return (r);
}

template <typename RetType, typename... Types>
std::string TestFuncCmp<RetType, Types...>::get_error() const
{
	std::string ret;

	ret = "with (";
	ret += tuple_to_str(this->_args, std::make_index_sequence<std::tuple_size<decltype(this->_args)>::value>());
	ret += ") ";
	ret += "expected " + std::to_string(this->_ret1);
	ret += " got " + std::to_string(this->_ret2);
	return ret;
}

#endif
