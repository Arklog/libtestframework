#ifndef DATABASE_H
#define DATABASE_H

#include "lib/sqlite3/sqlite3.h"
#include <chrono>
#include <exception>
#include <functional>
#include <iostream>
#include <string>

class TestBase;

class Database {
  private:
	sqlite3 *DB;
	std::string db_name;

	void create_name();
	void create_tables();
	int exec(std::string sql,
			 int (*callback)(void *, int, char **, char **) = NULL, void *addr = NULL);

	size_t get_test_id(std::string testname);

  public:
	Database();
	~Database();

	/**
	 * @brief Create the database
	 *
	 * The database will be created in the tmp directory with this name pattern
	 * [project_name hash]-[timestamp].testframework.db
	 */
	void create();

	void add_test(TestBase *);
	void add_result(std::string testname, size_t index, bool result,
					std::vector<std::tuple<size_t, std::string>> args);
};

#endif