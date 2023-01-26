#ifndef TEST_BASE_H
#define TEST_BASE_H

#include <functional>
#include <string>
#include <tuple>
#include <vector>


class TestBase {
  private:
	std::string testname;

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
};

#endif