#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H

#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <cerrno>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "testframework/Global/output.h"
#include "testframework/Socket/defines.h"

class SocketServer {
  private:
	int sock_fd;
	int connection_fd;
	ssize_t nreceived;
	t_socket_data d;
	sockaddr_un addr;

	bool finished;

  public:
	bool isFinished() const;

  private:
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
};

#endif