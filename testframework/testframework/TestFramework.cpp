#include "testframework/TestFramework.h"
#include "Loader/LibLoader.h"
#include "Socket/Client.h"
#include "Socket/Server.h"
#include "Test/TestBase.h"
#include "Test/TestManager.h"

TestFramework *TestFramework::instance = nullptr;
std::function<void(TestBase *)> TestFramework::test_added_callback = nullptr;
std::function<void(t_socket_data)> TestFramework::data_received_callback =
	nullptr;

TestFramework::TestFramework()
	: project_name(""), test_manager(nullptr), lib_loader(nullptr),
	  server_socket(nullptr), client_socket(nullptr) {
	TestBase::reset_id_counter();
}

TestFramework::~TestFramework() {
	if (this->test_manager)
		delete this->test_manager;
	if (this->lib_loader)
		delete this->lib_loader;
	if (this->server_socket)
		delete this->server_socket;
	if (this->client_socket)
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

bool TestFramework::init(std::string project_name) {
	TestBase::reset_id_counter();
	this->project_name = project_name;

	this->test_manager = new TestManager();

	this->lib_loader = new LibLoader();
	this->lib_loader->load(project_name);
	this->lib_loader->load_tests();

	this->server_socket = new SocketServer();
	this->client_socket = new SocketClient();

	return true;
}

void TestFramework::new_project(std::string project_name) {
	if (this->lib_loader)
		delete this->lib_loader;
	if (this->test_manager)
		delete this->test_manager;
	if (this->server_socket)
		delete this->server_socket;
	if (this->client_socket)
		delete this->client_socket;
	this->init(project_name);
}

void TestFramework::stop() { delete TestFramework::instance; }

std::string TestFramework::get_project_name() const {
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
	const std::function<void(TestBase *)> &testAddedCallback) {
	test_added_callback = testAddedCallback;
}
