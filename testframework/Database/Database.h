#ifndef DATABASE_H
#define DATABASE_H

#include <functional>
#include <string>
#include <iostream>
#include <chrono>
#include <exception>
#include "lib/sqlite3/sqlite3.h"

class Database {
  private:
	sqlite3 *DB;
	std::string db_name;

	void create_name();
	void create_tables();
	void exec(std::string sql);

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

	void add_test(std::string testname);
	void add_result(std::string testname, size_t index, bool result, std::vector<std::tuple<size_t, std::string>> args);
};

#endif