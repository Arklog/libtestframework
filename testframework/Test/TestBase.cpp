#include "testframework/Test/TestBase.h"

TestBase::TestBase(std::string name)
	: testname(name), result(true), finished(false) {}

TestBase::~TestBase() {}

bool TestBase::is_finished() const { return this->finished; }

std::string TestBase::get_name() const 
{
	return this->testname;
}

bool TestBase::run_one()
{
	return this->_run_one();
}

bool TestBase::run_all()
{
	return this->_run_all();
}