#ifndef TEST_BASE_H
#define TEST_BASE_H

#include "Socket/defines.h"
#include <functional>
#include <string>
#include <tuple>
#include <vector>

class TestBase {
  private:
	static size_t id_counter;
	size_t id;
	std::string testname;

	/**
	 * @brief callback function to call after a new test result have been
	 * received
	 *
	 */
	std::function<void(t_socket_data)> callback;

  protected:
	bool result;
	bool finished;

	virtual bool _run_one() = 0;
	virtual bool _run_all() = 0;

  public:
	TestBase(std::string name);
	virtual ~TestBase();

	std::string get_name() const;

	bool is_finished() const;
	bool run_one();
	bool run_all();

	virtual size_t get_test_numbers() const;
	size_t get_id() const;

	/**
	 * @brief Reset the id counter to zero, must be called before loading a new
	 * project
	 *
	 */
	static void reset_id_counter();
};

#endif