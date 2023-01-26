#include "testframework/Test/TestManager.h"
#include "testframework/Test/TestBase.h"
#include "testframework/Database/Database.h"
#include "testframework/testframework/TestFramework.h"

std::function<void(TestBase*)> TestManager::callback_add_test = [](TestBase *test)
{
	TestFramework::get_instance()->get_database()->add_test(test);
};

TestManager::TestManager() : test_list(std::vector<TestBase *>()) {}

TestBase *TestManager::get_next_test() {
	std::lock_guard<std::mutex> guard(this->test_list_mutex);
	if (this->test_list_iter == this->test_list.end())
		return nullptr;
	else
		return *(this->test_list_iter++);
}

TestManager::~TestManager() {
	for (auto test : this->test_list)
		delete test;
}

void TestManager::add_test(TestBase *test) {
	this->test_list.push_back(test);
	this->callback_add_test(test);
}

void TestManager::add_tests(std::vector<TestBase*> v)
{
	for (auto t: v)
		this->add_test(t);
}

void TestManager::execute_tests() {
	auto l = [this]() {
		TestBase *current_test;

		while ((current_test = this->get_next_test()))
			current_test->run_all();
	};

	for (std::array<std::thread, 4>::iterator iter = this->thead_list.begin();
		 iter != this->thead_list.end(); ++iter)
		*iter = std::thread(l);
	for (std::array<std::thread, 4>::iterator iter = this->thead_list.begin();
		 iter != this->thead_list.end(); ++iter)
		iter->join();
}