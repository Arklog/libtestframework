#include "testframework/testframework/TestFramework.h"
#include "testframework/Database/Database.h"
#include "testframework/Loader/LibLoader.h"
#include "testframework/Test/TestManager.h"

TestFramework *TestFramework::instance = nullptr;
TestFramework::TestFramework()
	: project_name(""), test_manager(nullptr), database(nullptr),
	  lib_loader(nullptr) {}

TestFramework::~TestFramework() {}

void TestFramework::set_instance(TestFramework *i) {
	TestFramework::instance = i;
}

TestFramework *TestFramework::get_instance() {
	if (!TestFramework::instance)
		TestFramework::instance = new TestFramework();
	return TestFramework::instance;
}

bool TestFramework::init(std::string project_name) {
	this->project_name = project_name;

	this->test_manager = new TestManager();

	this->database = new Database();
	this->database->create();

	this->lib_loader = new LibLoader();
	this->lib_loader->load(project_name);
	this->lib_loader->load_tests();

	return true;
}

void TestFramework::new_project(std::string project_name) {
	if (this->database)
		delete this->database;
	if (this->lib_loader)
		delete this->lib_loader;
	if (this->test_manager)
		delete this->test_manager;
	this->init(project_name);
}

std::string TestFramework::get_project_name() const {
	return this->project_name;
}

Database *TestFramework::get_database() { return this->database; }

TestManager *TestFramework::get_test_manager() { return this->test_manager; }