#ifndef TEST_MANAGER_H
#define TEST_MANAGER_H

#include <mutex>
#include <vector>
#include <array>
#include <thread>
#include <functional>

class TestBase;

class TestManager {
  private:
	std::mutex test_list_mutex;
	std::vector<TestBase *> test_list;
	std::vector<TestBase *>::iterator test_list_iter;

	std::array<std::thread, 4> thead_list;

	static std::function<void(TestBase*)> callback_add_test;

	TestBase *get_next_test();

  public:
	TestManager();
	~TestManager();

	void add_test(TestBase *test);
	void add_tests(std::vector<TestBase*> tests);
	void execute_tests();
};

#endif