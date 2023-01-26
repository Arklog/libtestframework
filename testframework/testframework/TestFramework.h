#ifndef TESTFRAMEWORK_H
#define TESTFRAMEWORK_H

#include "testframework/Database/Database.h"
class TestManager;
class LibLoader;

#include <string>
class TestFramework {
  private:
	std::string project_name;

	TestManager *test_manager;
	Database *database;
	LibLoader *lib_loader;

	static TestFramework *instance;
	TestFramework();

  public:
	~TestFramework();

	static void set_instance(TestFramework *);
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

	Database *get_database();
	TestManager *get_test_manager();
};

#endif