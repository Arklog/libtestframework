#include "testframework/Test/TestManager.h"
#include "testframework/Socket/Client.h"
#include "testframework/Socket/Server.h"
#include "testframework/Test/TestBase.h"
#include "testframework/testframework/TestFramework.h"
#include "testframework/Global/output.h"

TestManager::TestManager() : test_list(std::vector<TestBase *>()) {}

TestBase *TestManager::get_next_test() {
	std::lock_guard<std::mutex> guard(this->test_list_mutex);

	print_info("getting next test");
	if (this->test_list_iter == this->test_list.end()) {
		print_info("no test available");
		return nullptr;
	} else {
		print_info("next test found");
		return *(this->test_list_iter++);
	}
}

TestManager::~TestManager() {
	for (TestBase *test : this->test_list)
		delete test;
	this->test_list.clear();
}

void TestManager::add_test(TestBase *test) {
	std::lock_guard<std::mutex> guard(this->test_list_mutex);
	print_info("adding test ", test->get_name());
	this->test_list.push_back(test);
}

void TestManager::add_tests(std::vector<TestBase *> v) {
	for (auto t : v)
		this->add_test(t);
}

void TestManager::sort_tests() {}

void TestManager::execute_tests() {
	TestFramework::get_instance()->get_client_socket()->connect();
	this->test_list_iter = this->test_list.begin();

	auto l = [this]() {
		TestBase *current_test;
		print_info("starting thread");

		while ((current_test = this->get_next_test())) {
			print_info("new test started: ", current_test);
			current_test->run_all();
		}
		print_info("thread finished executing");
	};

	for (std::array<std::thread, 4>::iterator iter = this->thead_list.begin();
		 iter != this->thead_list.end(); ++iter)
		*iter = std::thread(l);
	for (std::array<std::thread, 4>::iterator iter = this->thead_list.begin();
		 iter != this->thead_list.end(); ++iter)
		iter->join();

	print_info("tests executed");
}

pid_t TestManager::fork_run() {
	pid_t pid;

	print_info("forking");

	pid = fork();
	if (pid == 0) {
		print_info("in child process, executing tests");
		sleep(1);
		this->execute_tests();

		return 0;
	} else {
		TestFramework::get_instance()->get_server_socket()->loop();
		return pid;
	}
}

const std::vector<TestBase *> TestManager::get_tests() {
	this->sort_tests();
	return this->test_list;
}