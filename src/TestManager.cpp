#include "TestManager.h"

std::shared_ptr<TestManager> TestManager::_current =
	std::shared_ptr<TestManager>(nullptr);

TestManager::TestManager(): _vec(std::vector<Test *>())
{
}

TestManager::~TestManager()
{
	std::vector<Test*>::iterator	iter;

	for (iter = this->_vec.begin(); iter != this->_vec.end(); ++iter)
		delete *iter;
}

std::shared_ptr<TestManager> TestManager::get()
{
	if (!TestManager::_current)
		TestManager::_current = std::shared_ptr<TestManager>(new TestManager());
	return TestManager::_current;
}

void	TestManager::add_test(Test *t)
{
	this->_vec.push_back(t);
}

std::vector<Test *> TestManager::get_tests()
{
	return (this->_vec);
}

std::vector<Test *>	TestManager::get_executed(bool all, bool success)
{
	std::vector<Test *>				vec;
	std::vector<Test *>::iterator	iter;

	for (iter = this->_vec.begin(); iter != this->_vec.end(); ++iter)
	{
		if ((*iter)->executed() && all)
			vec.push_back(*iter);
		else if ((*iter)->executed() && !all && (*iter)->result() == success)
			vec.push_back(*iter);
	}
	return (vec);
}

void	TestManager::run_one()
{
	auto	iter = this->_vec.begin();

	while (iter != this->_vec.end() && (*iter)->executed())
		++iter;
	if (iter != this->_vec.end())
		(*iter)->run();
}
