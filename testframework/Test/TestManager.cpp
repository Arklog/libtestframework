#include "testframework/Test/TestManager.h"
#include "testframework/Database/Database.h"
#include "testframework/Test/TestBase.h"
#include "testframework/testframework/TestFramework.h"

std::function<void(TestBase *)> TestManager::callback_add_test =
	[](TestBase *test) {
		TestFramework::get_instance()->get_database()->add_test(test);
	};

TestManager::TestManager() : test_list(std::vector<TestBase *>()) {}

TestBase *TestManager::get_next_test() {
	std::lock_guard<std::mutex> guard(this->test_list_mutex);

#ifdef DEBUG
	std::cout << "[INFO]: getting next test\n";
#endif
	if (this->test_list_iter == this->test_list.end()) {
#ifdef DEBUG
		std::cout << "[INFO]: no test available\n";
#endif
		return nullptr;
	} else {
#ifdef DEBUG
		std::cout << "[INFO]: next test found\n";
#endif
		return *(this->test_list_iter++);
	}
}

TestManager::~TestManager() {
	for (auto test : this->test_list)
		delete test;
}

void TestManager::add_test(TestBase *test) {
	this->test_list.push_back(test);
	this->callback_add_test(test);
}

void TestManager::add_tests(std::vector<TestBase *> v) {
	for (auto t : v)
		this->add_test(t);
}

void TestManager::execute_tests() {
	this->test_list_iter = this->test_list.begin();

	auto l = [this]() {
		TestBase *current_test;

#ifdef DEBUG
		std::cout << "[INFO]: starting thread\n";
#endif

		while ((current_test = this->get_next_test())) {

#ifdef DEBUG
			std::cout << "[INFO]: new test started (" << current_test
					  << std::endl;
#endif

			current_test->run_all();
		}

#ifdef DEBUG
		std::cout << "[INFO]: thread finished executing\n";
#endif
	};

	for (std::array<std::thread, 4>::iterator iter = this->thead_list.begin();
		 iter != this->thead_list.end(); ++iter)
		*iter = std::thread(l);
	for (std::array<std::thread, 4>::iterator iter = this->thead_list.begin();
		 iter != this->thead_list.end(); ++iter)
		iter->join();

#ifdef DEBUG
	std::cout << "[INFO]: all tests executed\n";
#endif
}

pid_t TestManager::fork_run() {
	pid_t pid;

#ifdef DEBUG
	std::cout << "[INFO]: forking\n" << std::endl;
#endif

	pid = fork();
	if (pid == 0) {
#ifdef DEBUG
		std::cout << "[INFO]: in child process, executing tests\n";
#endif

		this->execute_tests();

#ifdef DEBUG
		std::cout << "[INFO]: tests executed\n";
#endif

		_Exit(0);
	} else {
		return pid;
	}
}

const std::vector<TestBase *> TestManager::get_tests() const {
	return this->test_list;
}