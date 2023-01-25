#ifndef TEST_BASE_H
#define TEST_BASE_H

#include <string>
class TestBase {
  private:
	std::string testname;

  protected:
	bool result;
	bool finished;

  public:
	TestBase(std::string name);
	~TestBase();

	bool is_finished() const;
};

#endif