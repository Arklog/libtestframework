#include "testframework/Socket/Client.h"

SocketClient::SocketClient() : sock_fd(0), initialized(false) {
	memset(&addr, 0, sizeof(addr));
}
SocketClient::~SocketClient() {}

void SocketClient::connect() {
	int r;

#ifdef DEBUG
	cout_mutex.lock();
	std::cout << "[INFO]: client: connecting to server\n";
	cout_mutex.unlock();
#endif

	std::lock_guard<std::mutex> guard(sock_fd_mutex);
	sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock_fd == -1) {
#ifdef DEBUG
		std::cout << "[ERROR]: error creating socket: " << strerror(errno)
				  << std::endl;
#endif
		return;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, "/tmp/sk", sizeof(addr.sun_path));

	r = ::connect(sock_fd, (const struct sockaddr *)&this->addr,
				  sizeof(this->addr) - 1);

	if (r == -1) {
#ifdef DEBUG
		cout_mutex.lock();
		std::cout << "[ERROR]: could not connect socket: " << strerror(errno)
				  << std::endl;
		cout_mutex.unlock();
#endif
		return;
	} else {
#ifdef DEBUG
		cout_mutex.lock();
		std::cout << "[INFO]: client: connected to server\n";
		cout_mutex.unlock();
#endif
		initialized = true;
	}
}

void SocketClient::send(t_socket_data d) {
	int r;

	if (!initialized)
		this->connect();
	std::lock_guard<std::mutex> guard(this->sock_fd_mutex);

#ifdef DEBUG
	cout_mutex.lock();
	std::cout << "[INFO]: client: sending datas to server\n";
	cout_mutex.unlock();
#endif

	r = ::send(this->sock_fd, &d, sizeof(d), 0);

	if (r == -1) {
#ifdef DEBUG
		cout_mutex.lock();
		std::cout << "[ERROR]: error sending data to server: "
				  << strerror(errno) << std::endl;
		cout_mutex.unlock();
#endif
		_Exit(1);
	} else if (sizeof(d) != r) {
#ifdef DEBUG
		cout_mutex.lock();
		std::cout << "[ERROR]: send " << r << " bytes of datas instead of "
				  << sizeof(d) << std::endl;
		cout_mutex.unlock();
#endif
		_Exit(1);
	}

#ifdef DEBUG
	cout_mutex.lock();
	std::cout << "[INFO]: client: datas sent to server\n";
	cout_mutex.unlock();
#endif
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