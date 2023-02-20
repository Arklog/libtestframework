#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H

#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <cerrno>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include <functional>

#include "Global/output.h"
#include "Socket/defines.h"

class SocketServer {
  private:
	int sock_fd;
	sockaddr_un addr;

	std::mutex socket_datas_mutex;
	std::vector<t_socket_data> socket_datas;

	std::thread th;

	void create();
	void bind();
	void listen();
	void add_socket_data(t_socket_data d);

  public:
	SocketServer();
	~SocketServer();

	/**
	 * @brief Main loop
	 * 
	 */
	void loop();

	std::vector<t_socket_data> get_socket_datas();

	void clear_socket_datas();

	void start();
};

#endif