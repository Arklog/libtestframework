#include "testframework/Database/Database.h"
#include "testframework/testframework/TestFramework.h"

Database::Database() {}

Database::~Database() { sqlite3_close(this->DB); }

void Database::create_name() {
	std::size_t hash_value = std::hash<std::string>{}(
		TestFramework::get_instance()->get_project_name());
	auto now = std::chrono::system_clock::now();
	size_t timestamp = std::chrono::time_point_cast<std::chrono::seconds>(now)
						   .time_since_epoch()
						   .count();

	this->db_name = "/tmp/" + std::to_string(hash_value) + "-" +
					std::to_string(timestamp) + ".testframework.db";
}

void Database::create_tables() {
	std::string info_sql = "CREATE TABLE info("
						   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
						   "key TEXT NOT NULL, "
						   "value TEXT NOT NULL);";
	std::string test_sql = "CREATE TABLE test("
						   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
						   "name TEXT NOT NULL);";

	std::string result_sql = "CREATE TABLE result("
							 "id INTEGER PRIMARY KEY AUTOINCREMENT, "
							 "test_id NOT NULL, "
							 "test_index INTEGER NOT NULL, "
							 "result INTEGER NOT NULL, "
							 "FOREIGN KEY(test_id) REFERENCES test(id));";
	std::string arg_sql = "CREATE TABLE arg("
						  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
						  "result_id INTEGER NOT NULL, "
						  "pos INTEGER NOT NULL, "
						  "value TEXT, "
						  "FOREIGN KEY(result_id) REFERENCES result(id));";
	this->exec(info_sql);
	this->exec(test_sql);
	this->exec(result_sql);
	this->exec(arg_sql);
}

void Database::exec(std::string sql) {
	int code;
	char *error;

	code = sqlite3_exec(this->DB, sql.c_str(), NULL, 0, &error);
	if (code) {
		std::cout << "[ERROR]: " << error << std::endl << sql << std::endl;
		sqlite3_free(error);
	}
}
void Database::create() {
	int code;

	this->create_name();
	std::cout << this->db_name << std::endl;
	code = sqlite3_open(this->db_name.c_str(), &this->DB);
	if (code) {
		std::cout << "[ERROR]: " << code << std::endl;
	}
	this->create_tables();
}

void Database::add_test(std::string testname) {
	std::string sql = "INSERT INTO test (name) "
					  "VALUES ('" +
					  testname + "');";
	this->exec(sql);
}