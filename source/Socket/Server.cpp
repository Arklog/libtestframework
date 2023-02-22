#include "testframework/Socket/Server.h"
#include "testframework/testframework/TestFramework.h"

SocketServer::SocketServer() : sock_fd(0), finished(false) {
	memset(&addr, 0, sizeof(this->addr));
	addr.sun_family = AF_UNIX;
}

SocketServer::~SocketServer() {
	try {
		th.join();
	} catch (std::exception &e) {
		print_error("error joining thread", e.what());
	}
	close(sock_fd);
}

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
	this->create();
	this->bind();
	this->listen();

	connection_fd = accept(this->sock_fd, NULL, NULL);
	if (connection_fd == -1) {
		print_error("failed to accept connection:", strerror(errno));
		exit(1);
	} else {
		print_info("connection accepted");
	}

	th = std::thread([this]() {
		while ((this->nreceived =
					recv(this->connection_fd, &this->d, sizeof(this->d), 0))) {
			if (this->nreceived == -1) {
				print_error("failed to recv datas:", strerror(errno));
				exit(1);
			} else if (this->nreceived != sizeof(d)) {
				print_error("received", this->nreceived,
							"bytes of data instead of", sizeof(d));
				return;
			} else {
				print_info("received data for", this->d.testname, "number",
						   this->d.index);
				this->add_socket_data(this->d);
			}
		}
		close(this->connection_fd);
		this->finished = true;
	});
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

bool SocketServer::isFinished() const { return finished; }
