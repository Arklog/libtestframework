#ifndef TEST_MANAGER_H
#define TEST_MANAGER_H

#include <algorithm>
#include <array>
#include <cstring>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "testframework/Global/mutex.h"
#include "testframework/Socket/Client.h"
#include "testframework/utils/Fork.h"
#include "testframework/utils/SharedMemory.h"
#include "testframework/utils/ThreadWrapper.h"

class TestBase;

class TestManager {
  private:
	std::mutex test_list_mutex;
	std::vector<std::shared_ptr<TestBase>> test_list;
	std::vector<std::shared_ptr<TestBase>>::iterator test_list_iter;

	static std::function<void(std::shared_ptr<TestBase>)> callback_add_test;

	std::shared_ptr<TestBase> get_next_test();

  public:
	TestManager();
	~TestManager();

	/**
	 * @brief Add a test to the test manager
	 *
	 * @param test the test to add
	 */
	void add_test(std::shared_ptr<TestBase> test);

	/**
	 * @brief Add a vector of test to the test manager
	 *
	 * @param v the vector of test to add
	 */
	void add_tests(std::vector<std::shared_ptr<TestBase>> v);

	/**
	 * @brief Sort the tests by ascending order of ids, must be called before
	 * creating the test widgets.
	 *
	 */
	void sort_tests();

	/**
	 * @brief Execute the tests in multiple threads
	 *
	 */
	void execute_tests();

	/**
	 * @brief Start running the tests after forking
	 *
	 * @return int the child process pid
	 */
	pid_t fork_run();

	/**
	 * @brief Get the vector of tests object
	 *
	 * @return const std::vector<TestBase *>
	 */
	std::vector<std::shared_ptr<TestBase>> get_tests();
};

#endif