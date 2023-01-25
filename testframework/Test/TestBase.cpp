#include "testframework/Test/TestBase.h"

TestBase::TestBase(std::string name)
	: testname(name), result(true), finished(false) {}

TestBase::~TestBase() {}

bool TestBase::is_finished() const { return this->finished; }