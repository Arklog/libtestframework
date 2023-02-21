#include "testframework/Test/TestBase.h"

size_t TestBase::id_counter = 0;

void TestBase::reset_id_counter() { TestBase::id_counter = 0; }

TestBase::TestBase(std::string name)
	: id(TestBase::id_counter++), testname(name), result(true),
	  finished(false) {}

TestBase::~TestBase() {}

bool TestBase::is_finished() const { return this->finished; }

std::string TestBase::get_name() const { return this->testname; }

bool TestBase::run_one() { return this->_run_one(); }

bool TestBase::run_all() { return this->_run_all(); }

size_t TestBase::get_test_numbers() const { return 1; }

size_t TestBase::get_id() const { return this->id; }