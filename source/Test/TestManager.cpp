#include "testframework/Test/TestManager.h"
#include "testframework/Global/output.h"
#include "testframework/Socket/Client.h"
#include "testframework/Socket/Server.h"
#include "testframework/Test/TestBase.h"
#include "testframework/testframework/TestFramework.h"

TestManager::TestManager()
	: test_list(std::vector<std::shared_ptr<TestBase>>()) {}

std::shared_ptr<TestBase> TestManager::get_next_test() {
	std::lock_guard<std::mutex> guard(this->test_list_mutex);

	print_info("getting next test");
	if (this->test_list_iter != test_list.end()) {
		print_info("TestManager: test found");
		return *(test_list_iter++);
	} else {
		print_info("TestManager: no test found");
		return (nullptr);
	}
}

TestManager::~TestManager() { this->test_list.clear(); }

void TestManager::add_test(std::shared_ptr<TestBase> test) {
	std::lock_guard<std::mutex> guard(this->test_list_mutex);
	print_info("adding test ", test->get_name());
	this->test_list.push_back(test);
	auto callback = TestFramework::getTestAddedCallback();
	if (callback)
		callback(test);
}

void TestManager::add_tests(std::vector<std::shared_ptr<TestBase>> v) {
	for (auto t : v)
		this->add_test(t);
}

void TestManager::sort_tests() {}

void TestManager::execute_tests() {
	TestFramework::get_instance()->get_client_socket()->connect();
	std::array<ThreadWrapper, 4> thread_list{};

	test_list_iter = test_list.begin();
	auto l = [this]() {
		std::shared_ptr<TestBase> current_test;
		SharedMemory<t_socket_data> shared_mem;

		while ((current_test = this->get_next_test())) {
			print_info("new test started: ", current_test->get_name());
			// execute until finished
			while (!current_test->is_finished()) {
				Fork(
					[&shared_mem, &current_test]() {
						current_test->run_one();
						shared_mem.set(current_test->getSocketData());
						_Exit(0);
					},
					[]() {}, []() {},
					[&shared_mem, &current_test](int sig) {
						shared_mem.set(t_socket_data(sig));
					},
					[&shared_mem, &current_test]() {
						current_test->jump();
						TestFramework::get_instance()
							->get_client_socket()
							->send(*shared_mem.get());
					});
			}
		}
	};

	for (auto iter = thread_list.begin(); iter != thread_list.end(); ++iter)
		iter->newThread(l, "TestThread" + std::to_string(std::distance(
											  iter, thread_list.end())));
	print_info("TestManager: finished running tests");
}

pid_t TestManager::fork_run() {
	pid_t pid;

	print_info("TestManager: forking");

	pid = fork();
	if (pid == 0) {
		print_info("TestManager: in child process, executing tests");
		sleep(1);
		this->execute_tests();

		return 0;
	} else {
		print_info("TestManager: starting server");
		TestFramework::get_instance()->get_server_socket()->loop();
		return pid;
	}
}

std::vector<std::shared_ptr<TestBase>> TestManager::get_tests() {
	std::lock_guard<std::mutex> guard(test_list_mutex);

	this->sort_tests();
	return test_list;
}