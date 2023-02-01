#include "testframework/Test/TestManager.h"
#include "testframework/Socket/Client.h"
#include "testframework/Socket/Server.h"
#include "testframework/Test/TestBase.h"
#include "testframework/testframework/TestFramework.h"

TestManager::TestManager() : test_list(std::vector<TestBase *>()) {}

TestBase *TestManager::get_next_test() {
	std::lock_guard<std::mutex> guard(this->test_list_mutex);
	std::lock_guard<std::mutex> cguard(cout_mutex);

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
	for (TestBase *test : this->test_list)
		delete test;
	this->test_list.clear();
}

void TestManager::add_test(TestBase *test) {
	std::lock_guard<std::mutex> cguard(cout_mutex);
#ifdef DEBUG
	std::cout << "[INFO]: adding test: " << test->get_name() << std::endl;
#endif
	std::lock_guard<std::mutex> guard(this->test_list_mutex);
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
#ifdef DEBUG
		cout_mutex.lock();
		std::cout << "[INFO]: starting thread\n";
		cout_mutex.unlock();
#endif

		while ((current_test = this->get_next_test())) {

#ifdef DEBUG
			cout_mutex.lock();
			std::cout << "[INFO]: new test started (" << current_test
					  << std::endl;
			cout_mutex.unlock();
#endif

			current_test->run_all();
		}
#ifdef DEBUG
		cout_mutex.lock();
		std::cout << "[INFO]: thread finished executing\n";
		cout_mutex.unlock();
#endif
	};

	for (std::array<std::thread, 4>::iterator iter = this->thead_list.begin();
		 iter != this->thead_list.end(); ++iter)
		*iter = std::thread(l);
	for (std::array<std::thread, 4>::iterator iter = this->thead_list.begin();
		 iter != this->thead_list.end(); ++iter)
		iter->join();

#ifdef DEBUG
	cout_mutex.lock();
	std::cout << "[INFO]: tests executed\n";
	cout_mutex.unlock();
#endif
}

pid_t TestManager::fork_run() {
	pid_t pid;

#ifdef DEBUG
	cout_mutex.lock();
	std::cout << "[INFO]: forking\n" << std::endl;
	cout_mutex.unlock();
#endif

	pid = fork();
	if (pid == 0) {
#ifdef DEBUG
		cout_mutex.lock();
		std::cout << "[INFO]: in child process, executing tests\n";
		cout_mutex.unlock();
#endif
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