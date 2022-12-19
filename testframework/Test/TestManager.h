#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#ifndef MANAGER_THREADS
#define MANAGER_THREADS 8
#endif

#include "Test/Test.h"
#include <array>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

class TestManager {
private:
  static std::shared_ptr<TestManager> _current;
  /**
   * @brief Vector containing every test to be run
   */
  std::vector<Test *> _tests;
  /**
   * @brief Iterator to the last test run
   */
  std::vector<Test *>::iterator _iter;
  std::mutex _iter_mutex;

  std::array<std::thread, MANAGER_THREADS> _th;

  TestManager();

public:
  ~TestManager();

  /**
   * Return the current instance of the test manager
   *
   * @return		a shared pointer over the current instance of
   * 				the test manager
   */
  static std::shared_ptr<TestManager> get();

  /**
   * Add a new test to the test manager, it must be initialized
   * on the head as delete is called on deletion of the test manager
   *
   * @param t		the new test to be added
   */
  void add_test(Test *t);

  /**
   * Get the list of all tests
   *
   * @return		a vector object containing every test passed over
   *				the framework
   */
  std::vector<Test *> get_tests();

  /**
   * Return the list of all executed tests
   *
   * @param all			the vector should contain all executed tests
   * @param successfull	the vector should only contain passed tests,
   * 						if false the vector should only
   * contain unsuccessfull one
   *
   * @return		a vector containing every test that have been executed
   * so far
   */
  std::vector<Test *> get_executed(bool all = true, bool successfull = true);

  /**
   * Execute one test
   *
   * @return		true if a test have been run, false else
   */
  bool run_one();

  void run_all();
  bool finished() const;
};

#endif
