#include "testframework/Socket/Server.h"

SocketServer::SocketServer() : sock_fd(0) {
	memset(&addr, 0, sizeof(this->addr));
	addr.sun_family = AF_UNIX;
}

SocketServer::~SocketServer() {}

void SocketServer::create() {
	sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock_fd == -1) {
#ifdef DEBUG
		cout_mutex.lock();
		std::cout << "[ERROR]: could not create socket: " << strerror(errno)
				  << std::endl;
		cout_mutex.unlock();
#endif
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
#ifdef DEBUG
		cout_mutex.lock();
		std::cout << "[ERROR]: could not bind socket: " << strerror(errno)
				  << std::endl;
		cout_mutex.unlock();
#endif
		exit(1);
	}
}

void SocketServer::listen() {
	int ret;

	ret = ::listen(this->sock_fd, 0);
	if (ret == -1) {
#ifdef DEBUG
		std::cout << "[ERROR]: failed to listen: " << strerror(errno)
				  << std::endl;
#endif
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
#ifdef DEBUG
		std::cout << "[ERROR]: failed to accept connection: " << strerror(errno)
				  << std::endl;
#endif
		exit(1);
	} else {
#ifdef DEBUG
		cout_mutex.lock();
		std::cout << "[INFO]: server: connection accepted\n";
		cout_mutex.unlock();
#endif
	}

	while ((n = recv(fd, &d, sizeof(d), 0))) {
		if (n == -1) {
#ifdef DEBUG
			cout_mutex.lock();
			std::cout << "[ERROR]: failed to recv datas: " << strerror(errno)
					  << std::endl;
			cout_mutex.unlock();
#endif
			exit(1);
		} else if (n != sizeof(d)) {
#ifdef DEBUG
			cout_mutex.lock();
			std::cout << "[ERROR]: received " << n
					  << "bytes of data instead of " << sizeof(d) << std::endl;
			cout_mutex.unlock();
#endif
			return;
		} else {
#ifdef DEBUG
			cout_mutex.lock();
			std::cout << "[INFO]: received datas for " << d.testname
					  << " number " << d.index << std::endl;
			cout_mutex.unlock();
#endif
			this->add_socket_data(d);
		}
	}
}

std::vector<t_socket_data> SocketServer::get_socket_datas() {
	std::vector<t_socket_data> v;
	std::lock_guard<std::mutex> guard(this->socket_datas_mutex);

	v = this->socket_datas;
	this->socket_datas.erase(this->socket_datas.begin(),
							 this->socket_datas.end());
	return v;
}