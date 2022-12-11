#include "Test.h"

Test::Test()
{
}

Test::~Test()
{
}

bool	Test::executed() const
{
	return this->_exec;
}

bool	Test::result() const
{
	return this->_result;
}

std::vector<std::string>	Test::to_string() const
{
	std::vector<std::string>	vec;

	if (!this->executed())
		return (vec.push_back("[*]"), vec);
	else
		return (vec.push_back((this->result()) ? "[OK]" : "[KO]"), vec);
}
