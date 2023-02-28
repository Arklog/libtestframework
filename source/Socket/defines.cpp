//
// Created by pierre on 27/02/23.
//
#include "testframework/Socket/defines.h"
#include "testframework/Test/TestBase.h"

s_socket_data::s_socket_data() { zero(); }

s_socket_data::s_socket_data(
	TestBase *test, size_t index, bool result,
	const std::vector<std::tuple<size_t, std::string>> &args, std::string msg) {
	zero();

	strncpy(testname, test->get_name().c_str(), SOCKET_BUFF_SIZE - 1);
	this->id = test->get_id();
	this->index = index;
	this->result = result;
	this->nargs = (args.size() <= 10) ? args.size() : 10;

	for (size_t i = 0; i < nargs; ++i)
		strncpy(this->args[i], std::get<1>(args.at(i)).c_str(),
				SOCKET_BUFF_SIZE - 1);

	strncpy(this->message, msg.c_str(), SOCKET_MESSAGE_BUFF_SIZE - 1);
}

void s_socket_data::zero() {
	std::memset(this->message, 0, sizeof(this->message));
	std::memset(this->args, 0, sizeof(this->args));
	id = 0;
	index = 0;
	nargs = 0;
	result = false;
	crashed = false;
	crash_value = 0;
}
s_socket_data::s_socket_data(int signal) {
	zero();
	crashed = true;
	crash_value = signal;
	strncpy(message, strsignal(signal), SOCKET_MESSAGE_BUFF_SIZE - 1);
}

s_socket_data::~s_socket_data() = default;
