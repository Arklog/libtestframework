#include "TestSuite.h"

TestSuite::TestSuite(std::string name): _name(name), _tests(std::vector<Test *>())
{
}

TestSuite::TestSuite(std::string name, std::vector<Test *> tests):
	_name(name), _tests(tests)
{
}

TestSuite::~TestSuite()
{
	std::vector<Test *>::iterator	iter;

	for (iter = this->_tests.begin(); iter != this->_tests.end(); ++iter)
		delete *iter;
}

void	TestSuite::run()
{
	auto	iter = this->_tests.begin();

	if (this->executed())
		return ;
	for (;iter != this->_tests.end(); ++iter)
	{
		if (!(*iter)->executed())
			return ((void)(*iter)->run());
	}
}

std::string	TestSuite::name() const
{
	return this->_name;
}

std::vector<std::string>	TestSuite::to_string() const
{
	std::vector<std::string>	vec;
	std::string					str;

	str = std::string("");
	str.append(
			this->name()).append(
			std::string(": []\n").insert(3, 
				(this->executed()) ? (this->result()) ? "OK" : "KO" : "*"));
	vec.push_back(str);
	str = std::string("");
	for (Test *iter: this->_tests)
		str.append(iter->to_string().at(0) + " ");
	vec.push_back(str);
	return (vec);
}

std::string	TestSuite::get_error() const
{
	std::string	str;

	str = this->name() + "\n";
	for (auto iter: this->_tests)
	{
		if (iter->executed() && !iter->result())
			str += iter->get_error() + "\n";
	}

	return (str);
}

bool	TestSuite::result() const
{
	for (Test *iter: this->_tests)
		if (!iter->result())
			return (false);
	return (true);
}

bool	TestSuite::executed() const
{
	if (this->_exec)
		return (true);
	for (auto i: this->_tests)
		if (!i->executed())
			return (false);
	return (true);
}
