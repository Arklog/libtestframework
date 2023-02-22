#ifndef TESTFRAMEWORK_H
#define TESTFRAMEWORK_H

#include "testframework/Socket/defines.h"
#include "testframework/utils/ThreadWrapper.h"
#include <functional>
#include <string>
#include <thread>
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
	ThreadWrapper th;
	TestManager *test_manager;
	LibLoader *lib_loader;
	SocketServer *server_socket;
	SocketClient *client_socket;

	static TestFramework *instance;
	TestFramework();

  public:
	~TestFramework();
	static void set_instance(TestFramework *);
	static TestFramework *get_instance();

	/**
	 * @brief Initialise the framework
	 *
	 * @param _project_name the name of the current project
	 *
	 * @return 1 on success, 0 else
	 */
	bool init(const std::string &_project_name);

	/**
	 * @brief Setup the framework again for a new series of tests
	 *
	 * @param _project_name the name of the test library to load
	 */
	[[maybe_unused]] void new_project(std::string _project_name);

	/**
	 * @brief Stop the framework and clear memory
	 *
	 */
	static void stop();

	void start();

	[[nodiscard]] std::string get_project_name() const;

	TestManager *get_test_manager();

	SocketServer *get_server_socket();

	SocketClient *get_client_socket();

	/**
	 * Contain a callback called when a new test is added to the framework
	 */
	static std::function<void(TestBase *)> test_added_callback;

	/**
	 * Contain a callback called when the server receive the result for a test
	 */
	static std::function<void(t_socket_data)> data_received_callback;

	/**
	 * getter for data_received callback
	 * @return
	 */
	static const std::function<void(t_socket_data)> &getDataReceivedCallback();

	/**
	 * getter for test_added_callback
	 * @return
	 */
	static const std::function<void(TestBase *)> &getTestAddedCallback();

	static void setDataReceivedCallback(
		const std::function<void(t_socket_data)> &dataReceivedCallback);

	static void setTestAddedCallback(
		const std::function<void(TestBase *)> &testAddedCallback);
};

#endif