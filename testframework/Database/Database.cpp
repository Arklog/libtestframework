#include "testframework/Database/Database.h"
#include "testframework/Test/TestBase.h"
#include "testframework/testframework/TestFramework.h"

Database::Database() { sqlite3_initialize(); }

Database::~Database() {}

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
							 "test_id INTEGER NOT NULL, "
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

int Database::exec(std::string sql,
				   int (*callback)(void *, int, char **, char **), void *addr) {
	int code;
	char *error;

	std::lock_guard<std::mutex> guard(this->DB_mutex);

	sqlite3_open(this->db_name.c_str(), &this->DB);

	code = sqlite3_exec(this->DB, sql.c_str(), callback, addr, &error);
	if (code) {
		std::cout << "[ERROR]: " << error << std::endl << sql << std::endl;
		sqlite3_free(error);
		return -1;
	}

	sqlite3_close(this->DB);
	return sqlite3_last_insert_rowid(this->DB);
}

size_t Database::get_test_id(std::string testname) {
	int id;
	std::string sql = "SELECT id FROM test WHERE name='" + testname + "';";
	auto l = [](void *addr, int n, char **vals, char **names) -> int {
		(void)names;
		if (!n || !vals || !vals[0])
			return 1;
		if (addr)
			*((int *)addr) = atoi(vals[0]);
		return 0;
	};

#ifdef DEBUG
	std::cout << "[INFO]: get_test_id callback\n";
#endif

	this->exec(sql, l, &id);
	return id;
}

void Database::create() {
	this->create_name();

#ifdef DEBUG
	std::cout << "[INFO]: db name " << this->db_name << std::endl;
#endif

	this->create_tables();
}

void Database::add_test(const TestBase *test) {
	std::string sql = "INSERT INTO test (name) "
					  "VALUES ('" +
					  test->get_name() + "');";
	this->exec(sql);
}

void Database::add_result(std::string testname, size_t index, bool result,
						  std::vector<std::tuple<size_t, std::string>> args) {
	int row_id;

	std::string sql =
		"INSERT INTO result (test_id, test_index, result) VALUES(" +
		std::to_string(this->get_test_id(testname)) + ", " +
		std::to_string(index) + ", " + std::to_string(result) + ");";
	row_id = this->exec(sql);
	for (auto arg : args) {
		sql = "INSERT INTO arg(result_id, pos, value) VALUES (" +
			  std::to_string(row_id) + ", " + std::to_string(std::get<0>(arg)) +
			  ", " + std::get<1>(arg) + ");";
		this->exec(sql);
	}
}

std::string Database::get_db_name() const { return this->db_name; }

std::vector<t_arg> Database::get_args_for_result(int result_id) {
	std::string sql = "SELECT id,pos,value FROM arg WHERE result_id=" +
					  std::to_string(result_id) + ";";
	auto l = [](void *addr, int n, char **vals, char **field) {
		t_arg a;
		std::vector<t_arg> *v = (std::vector<t_arg> *)addr;

		a.id = atoi(vals[0]);
		a.pos = atoi(vals[1]);
		a.value = std::string(vals[2]);

		(void)n;
		(void)field;
		v->push_back(a);
		return 0;
	};
	std::vector<t_arg> v;

	this->exec(sql, l, &v);
	return v;
}

std::vector<t_result> Database::get_result_for_test(int test_id) {
	std::string sql = "SELECT id,test_index,result FROM result WHERE test_id=" +
					  std::to_string(test_id) + ";";
	auto l = [](void *addr, int n, char **vals, char **fields) {
		t_result r;
		std::vector<t_result> *v = (std::vector<t_result> *)addr;

		r.id = atoi(vals[0]);
		r.index = atoi(vals[1]);
		r.result = bool(atoi(vals[2]));

		(void)n;
		(void)fields;
		v->push_back(r);
		return (0);
	};

	std::vector<t_result> v;
	this->exec(sql, l, &v);

	for (auto i : v)
		i.args = this->get_args_for_result(i.id);

	return v;
}

t_test Database::get_test_info(std::string name) {
	std::string sql = "SELECT id,name from test WHERE name = '" + name + "';";
	t_test t;
	auto l = [](void *addr, int n, char **val, char **fields) {
		t_test t;

		t.id = atoi(val[0]);
		t.name = std::string(val[1]);

		(void)n;
		(void)fields;

		*(t_test *)addr = t;
		return (0);
	};

	this->exec(sql, l, &t);
	t.results = this->get_result_for_test(t.id);
	return t;
}