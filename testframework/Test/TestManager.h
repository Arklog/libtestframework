#ifndef TEST_MANAGER_H
#define TEST_MANAGER_H

#include <algorithm>
#include <array>
#include <cstring>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "testframework/Global/mutex.h"

class TestBase;

class TestManager {
  private:
	std::mutex test_list_mutex;
	std::vector<TestBase *> test_list;
	std::vector<TestBase *>::iterator test_list_iter;

	std::array<std::thread, 4> thead_list;

	static std::function<void(TestBase *)> callback_add_test;

	TestBase *get_next_test();

  public:
	TestManager();
	~TestManager();

	/**
	 * @brief Add a test to the test manager
	 *
	 * @param test the test to add
	 */
	void add_test(TestBase *test);

	/**
	 * @brief Add a vector of test to the test manager
	 *
	 * @param tests the vector of test to add
	 */
	void add_tests(std::vector<TestBase *> tests);

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
	const std::vector<TestBase *> get_tests();
};

#endif