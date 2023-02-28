#ifndef TEST_BASE_H
#define TEST_BASE_H

#include "testframework/Socket/defines.h"
#include <functional>
#include <string>
#include <tuple>
#include <vector>

class TestBase {
  private:
	static size_t id_counter;
	size_t id;
	std::string testname;

  protected:
	bool result;
	bool finished;
	struct s_socket_data socket_data;

	virtual bool _run_one() = 0;
	virtual bool _run_all() = 0;

  public:
	TestBase(std::string name);
	virtual ~TestBase();

	std::string get_name() const;

	/**
	 * Check if this test is finished
	 * @return
	 */
	bool is_finished() const;

	/**
	 * Run one test
	 * @return
	 */
	bool run_one();

	/**
	 * Jump one test
	 */
	virtual void jump() = 0;

	/**
	 * Run all tests
	 * @return
	 */
	bool run_all();

	/**
	 * Return the total number of subtests to be run
	 * @return
	 */
	virtual size_t get_test_numbers() const;

	size_t get_id() const;

	/**
	 * @brief Reset the id counter to zero, must be called before loading a new
	 * project
	 *
	 */
	static void reset_id_counter();

	const struct s_socket_data &getSocketData() const;
};

#endif