#ifndef TESTFRAMEWORK_H
#define TESTFRAMEWORK_H

#define TESTFRAMEWORK_VERSION_MAJOR 0
#define TESTFRAMEWORK_VERSION_MINOR 0

#include <string>
#include <vector>

class TestBase;
class TestManager;
class LibLoader;
class SocketServer;
class SocketClient;

class TestFramework {
  private:
	std::string project_name;

	TestManager *test_manager;
	LibLoader *lib_loader;
	SocketServer *server_socket;
	SocketClient *client_socket;

	static TestFramework *instance;
	TestFramework();

  public:
	~TestFramework();

	static void set_instance(TestFramework *);
	static TestBase *create_test_array(std::vector<TestBase *> v);
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

	/**
	 * @brief Stop the framework and clear memory
	 *
	 */
	void stop();

	std::string get_project_name() const;

	TestManager *get_test_manager();

	SocketServer *get_server_socket();

	SocketClient *get_client_socket();
};

#endif