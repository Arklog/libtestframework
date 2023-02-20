#ifndef TESTFRAMEWORK_H
#define TESTFRAMEWORK_H

#include "Socket/defines.h"
#include <functional>
#include <string>
#include <vector>

class TestBase;
class TestManager;
class LibLoader;
class SocketServer;
class SocketClient;

const int LIBTESTFRAMEWORK_VERSION_MAJOR = 0;
const int LIBTESTFRAMEWORK_VERSION_MINOR = 0;

class TestFramework {
  private:
	std::string project_name;

	TestManager *test_manager;
	LibLoader *lib_loader;
	SocketServer *server_socket;
	SocketClient *client_socket;

	static TestFramework *instance;
	TestFramework();

	static std::function<void(TestBase *)> test_added_callback;
	static std::function<void(t_socket_data)> data_received_callback;

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

	/**
	 * @brief Stop the framework and clear memory
	 *
	 */
	void stop();

	[[nodiscard]] std::string get_project_name() const;

	TestManager *get_test_manager();

	SocketServer *get_server_socket();

	SocketClient *get_client_socket();

	static void setDataReceivedCallback(
		const std::function<void(t_socket_data)> &dataReceivedCallback);

	static std::function<void(t_socket_data)> getDataReceivedCallback();

	static void setTestAddedCallback(
		const std::function<void(TestBase *)> &testAddedCallback);
};

#endif