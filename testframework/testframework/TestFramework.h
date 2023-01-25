#ifndef TESTFRAMEWORK_H
#define TESTFRAMEWORK_H

#include <string>
class TestFramework {
  private:
	std::string project_name;
	static TestFramework *instance;
	TestFramework();

  public:
	~TestFramework();
	static TestFramework *get_instance();

	/**
	* @brief Initialise the framework
	*
	* @param project_name the name of the current project
	*
	* @return 1 on success, 0 else
	*/
	bool init(std::string project_name);

	void new_project(std::string project_name);

	std::string get_project_name() const;
};

#endif