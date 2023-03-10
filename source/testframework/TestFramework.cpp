#include <sys/wait.h>
#include <utility>

#include "testframework/Loader/LibLoader.h"
#include "testframework/Socket/Client.h"
#include "testframework/Socket/Server.h"
#include "testframework/Test/TestBase.h"
#include "testframework/Test/TestManager.h"
#include "testframework/testframework/TestFramework.h"

TestFramework *TestFramework::instance = nullptr;

std::function<void(std::shared_ptr<TestBase>)>
	TestFramework::test_added_callback = nullptr;

std::function<void(t_socket_data)> TestFramework::data_received_callback =
	nullptr;

TestFramework::TestFramework()
	: project_name(), th(), test_manager(nullptr), lib_loader(nullptr),
	  server_socket(nullptr), client_socket(nullptr), _should_stop(false) {
	print_info("TestFramework: initializing instance");
	TestBase::reset_id_counter();
}

TestFramework::~TestFramework() {
	print_info("TestFramework: killing current instance");
	delete this->test_manager;
	delete this->lib_loader;
	delete this->server_socket;
	delete this->client_socket;
}

void TestFramework::set_instance(TestFramework *i) {
	TestFramework::instance = i;
}

TestFramework *TestFramework::get_instance() {
	if (!TestFramework::instance)
		TestFramework::instance = new TestFramework();
	return TestFramework::instance;
}

bool TestFramework::init(const std::string &_project_name) {
	print_info("TestFramework: initializing project", _project_name);
	TestBase::reset_id_counter();
	this->project_name = _project_name;

	this->test_manager = new TestManager();

	this->lib_loader = new LibLoader();
	this->lib_loader->load(_project_name);
	this->lib_loader->load_tests();

	this->server_socket = new SocketServer();
	this->client_socket = new SocketClient();

	_should_stop = false;

	return true;
}

[[maybe_unused]] void TestFramework::new_project(std::string _project_name) {
	print_info("TestFramework: preparing for project", _project_name);
	delete this->lib_loader;
	delete this->test_manager;
	delete this->server_socket;
	delete this->client_socket;
	this->init(_project_name);
}

[[maybe_unused]] std::string TestFramework::get_project_name() const {
	return this->project_name;
}

TestManager *TestFramework::get_test_manager() { return this->test_manager; }

SocketServer *TestFramework::get_server_socket() { return this->server_socket; }

SocketClient *TestFramework::get_client_socket() { return this->client_socket; }

void TestFramework::setDataReceivedCallback(
	const std::function<void(t_socket_data)> &dataReceivedCallback) {
	data_received_callback = dataReceivedCallback;
}

void TestFramework::setTestAddedCallback(
	const std::function<void(std::shared_ptr<TestBase>)> &testAddedCallback) {
	test_added_callback = testAddedCallback;
}

const std::function<void(std::shared_ptr<TestBase>)> &
TestFramework::getTestAddedCallback() {
	return test_added_callback;
}

const std::function<void(t_socket_data)> &
TestFramework::getDataReceivedCallback() {
	return data_received_callback;
}

void TestFramework::start() {
	print_info("TestFramework: start execution");
	this->th.newThread(std::function<void()>([]() {
						   print_info("MainThread: start");
						   auto instance = TestFramework::get_instance();
						   pid_t pid = instance->get_test_manager()->fork_run();

						   waitpid(pid, nullptr, 0);
						   instance->setShouldStop(true);
						   print_info("TestManager: finished");
					   }),
					   "MainThread");
}

bool TestFramework::isShouldStop() const { return _should_stop; }

void TestFramework::setShouldStop(bool shouldStop) {
	_should_stop = shouldStop;
}

void TestFramework::stop() { delete TestFramework::instance; }
