#ifndef TESTFUNCCMPGEN_H
#define TESTFUNCCMPGEN_H

#include <iostream>

#include "Test/TestFuncCmp.h"
#include "Generator/GeneratorList.h"

template <typename RetType, typename... Types>
class TestFuncCmpGen : public Test
{
private:
	std::function<RetType(Types...)> _f1;
	std::function<RetType(Types...)> _f2;
	TestFuncCmp<RetType, Types...> *_cmp;
	GeneratorList<Types...> *_gen;

public:
	TestFuncCmpGen<RetType, Types...>(std::function<RetType(Types...)> f1,
									  std::function<RetType(Types...)> f2,
									  GeneratorList<Types...> *glist);
	~TestFuncCmpGen();

	std::vector<std::string> to_string() const override;
	std::string get_error() const override;
	void run() override;
};

template <typename RetType, typename... Types>
TestFuncCmpGen<RetType, Types...>::TestFuncCmpGen(
	std::function<RetType(Types...)> f1,
	std::function<RetType(Types...)> f2,
	GeneratorList<Types...> *glist) : Test(), _f1(f1), _f2(f2), _cmp(nullptr), _gen(glist)
{
	this->_result = true;
	this->_cmp = new TestFuncCmp<RetType, Types...>(this->_f1, this->_f2, this->_gen->get_nth(0));
}

template <typename RetType, typename... Types>
TestFuncCmpGen<RetType, Types...>::~TestFuncCmpGen()
{
	delete this->_cmp;
	delete this->_gen;
}

template <typename RetType, typename... Types>
std::vector<std::string> TestFuncCmpGen<RetType, Types...>::to_string() const
{
	std::vector<std::string> i = std::vector<std::string>();
	std::string str;

	if (this->executed())
		str += (this->result()) ? "[OK]" : "[KO]";
	else
		str += '[' + std::to_string(this->_gen->get_current()) + '/' + std::to_string(this->_gen->get_max()) + ']';
	i.push_back(str);
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
	if (this->executed())
		return;
	this->_cmp->set_args(this->_gen->get_next());
	this->_cmp->run();
	this->_result &= this->_cmp->result();
	if (!this->_result || this->_gen->get_current() == this->_gen->get_max())
		this->_exec = true;
}

#endif