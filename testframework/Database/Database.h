#ifndef DATABASE_H
#define DATABASE_H

#include "lib/sqlite3/sqlite3.h"

#include <chrono>
#include <exception>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>

#include "testframework/Database/QueryResult.h"

class TestBase;

class Database {
  private:
	std::mutex DB_mutex;
	sqlite3 *DB;

	std::string db_name;

	void create_name();
	void create_tables();
	int exec(std::string sql,
			 int (*callback)(void *, int, char **, char **) = NULL,
			 void *addr = NULL);

	size_t get_test_id(std::string testname);

	std::vector<t_arg> get_args_for_result(int result_id);
	std::vector<t_result> get_result_for_test(int test_id);

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

	/**
	 * @brief Add a test to the database
	 *
	 * @param t The test to be added
	 */
	void add_test(const TestBase *t);

	/**
	 * @brief Add a test result and the arguments of the test to the database
	 *
	 * @param testname the name of the test from which the result are added
	 * @param index the index of this run of the test
	 * @param result the result of the test
	 * @param args a list of arguments positions and values
	 */
	void add_result(std::string testname, size_t index, bool result,
					std::vector<std::tuple<size_t, std::string>> args);

	std::string get_db_name() const;

	/**
	 * @brief Get all informations about a test
	 *
	 * @param name the test's name
	 * @return t_test
	 */
	t_test get_test_info(std::string name);
};

#endif