#include "testframework/Socket/Client.h"

SocketClient::SocketClient() : sock_fd(0), initialized(false) {
	memset(&addr, 0, sizeof(addr));
}
SocketClient::~SocketClient() {}

void SocketClient::connect() {
	int r;

	print_info("client connecting to server");

	std::lock_guard<std::mutex> guard(sock_fd_mutex);
	sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock_fd == -1) {
		print_error("error creating socket:", strerror(errno));
		return;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, "/tmp/sk", sizeof(addr.sun_path));

	r = ::connect(sock_fd, (const struct sockaddr *)&this->addr,
				  sizeof(this->addr) - 1);

	if (r == -1) {
		print_error("client could not connect to server socket:",
					strerror(errno));
		return;
	} else {
		print_info("client connected to server");
		initialized = true;
	}
}

void SocketClient::send(t_socket_data d) {
	int r;

	if (!initialized)
		this->connect();
	std::lock_guard<std::mutex> guard(this->sock_fd_mutex);

	print_info("client sending data to server");

	r = ::send(this->sock_fd, &d, sizeof(d), 0);

	if (r == -1) {
		print_error("client:", strerror(errno));
		_Exit(1);
	} else if (sizeof(d) != r) {
		print_error("client: sent", r, "bytes of data instead of", sizeof(d));
		_Exit(1);
	}
	print_info("client: data successfully send");
}

void SocketClient::send(size_t id, std::string testname, std::string *args,
						int index, int nargs, bool result) {
	t_socket_data d;
	memset(&d, 0, sizeof(d));

	d.id = id;
	d.index = index;
	strncpy(d.testname, testname.c_str(), sizeof(d.testname) - 1);
	for (int i = 0; i < SOCKET_NARGS; ++i)
		strncpy(d.args[i], args[i].c_str(), sizeof(d.args[i]) - 1);
	d.nargs = nargs;
	d.result = result;

	this->send(d);
}