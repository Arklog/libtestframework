#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

#include <sys/socket.h>
#include <sys/un.h>

#include <cerrno>
#include <cstring>
#include <iostream>
#include <mutex>
#include <string>

#include "testframework/Global/mutex.h"
#include "testframework/Global/output.h"
#include "testframework/Socket/defines.h"

class SocketClient {
  private:
	std::mutex sock_fd_mutex;
	int sock_fd;
	sockaddr_un addr;

	bool initialized;

  public:
	SocketClient();
	~SocketClient();

	void send(t_socket_data d);

	void send(size_t id, std::string testname, std::string args[SOCKET_NARGS],
			  int index, int nargs, bool result);
	void connect();
};

#endif