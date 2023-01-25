#include "testframework/testframework/TestFramework.h"

TestFramework* TestFramework::instance = nullptr;
TestFramework::TestFramework() {}

TestFramework::~TestFramework() {}

TestFramework* TestFramework::get_instance()
{
	if (!TestFramework::instance)
		TestFramework::instance = new TestFramework();
	return TestFramework::instance;
}
bool TestFramework::init(std::string project_name)
{
	this->project_name = project_name;

	return true;
}

std::string TestFramework::get_project_name() const
{
	return this->project_name;
}