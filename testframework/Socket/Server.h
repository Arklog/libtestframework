#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/fcntl.h>

#include <cerrno>
#include <iostream>
#include <mutex>
#include <vector>

#include "testframework/Socket/defines.h"
#include "testframework/Global/mutex.h"

class SocketServer {
  private:
	int sock_fd;
	sockaddr_un addr;

	std::mutex socket_datas_mutex;
	std::vector<t_socket_data> socket_datas;

	void create();
	void bind();
	void listen();
	void add_socket_data(t_socket_data d);
  public:
	SocketServer();
	~SocketServer();

	void loop();
	std::vector<t_socket_data> get_socket_datas();
};

#endif