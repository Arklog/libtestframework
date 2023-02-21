#include "testframework/Socket/Server.h"

SocketServer::SocketServer() : sock_fd(0) {
	memset(&addr, 0, sizeof(this->addr));
	addr.sun_family = AF_UNIX;
}

SocketServer::~SocketServer() {}

void SocketServer::create() {
	sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock_fd == -1) {
		print_error("could not create socket:", strerror(errno));
		exit(1);
	}
}

void SocketServer::bind() {
	int ret;

	remove("/tmp/sk");
	strncpy(this->addr.sun_path, "/tmp/sk", sizeof(this->addr.sun_path) - 1);
	ret = ::bind(this->sock_fd, (const struct sockaddr *)&this->addr,
				 sizeof(this->addr));
	if (ret == -1) {
		print_error("could not bind socket:", strerror(errno));
		exit(1);
	}
}

void SocketServer::listen() {
	int ret;

	ret = ::listen(this->sock_fd, 0);
	if (ret == -1) {
		print_error("could not listen:", strerror(errno));
		exit(1);
	}
}

void SocketServer::add_socket_data(t_socket_data d) {
	std::lock_guard<std::mutex> guard(this->socket_datas_mutex);
	this->socket_datas.push_back(d);
}

void SocketServer::loop() {
	int fd;
	t_socket_data d;
	int n;

	this->create();
	this->bind();
	this->listen();

	fd = accept(this->sock_fd, NULL, NULL);
	if (fd == -1) {
		print_error("failed to accept connection:", strerror(errno));
		exit(1);
	} else {
		print_info("connection accepted");
	}

	while ((n = recv(fd, &d, sizeof(d), 0))) {
		if (n == -1) {
			print_error("failed to recv datas:", strerror(errno));
			exit(1);
		} else if (n != sizeof(d)) {
			print_error("received", n, "bytes of data instead of", sizeof(d));
			return;
		} else {
			print_info("received data for", d.testname, "number", d.index);
			this->add_socket_data(d);
		}
	}
	print_info("server loop finished");
}

std::vector<t_socket_data> SocketServer::get_socket_datas() {
	std::vector<t_socket_data> v;
	std::lock_guard<std::mutex> guard(this->socket_datas_mutex);

	v = this->socket_datas;
	return v;
}

void SocketServer::clear_socket_datas() {
	std::lock_guard<std::mutex> guard(this->socket_datas_mutex);
	socket_datas.clear();
}