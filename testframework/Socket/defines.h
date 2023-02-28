#ifndef SOCKET_DEFINES_H
#define SOCKET_DEFINES_H

#ifndef SOCKET_BUFF_SIZE
#define SOCKET_BUFF_SIZE 256
#endif

#ifndef SOCKET_MESSAGE_BUFF_SIZE
#define SOCKET_MESSAGE_BUFF_SIZE 512
#endif

#ifndef SOCKET_NARGS
#define SOCKET_NARGS 10
#endif

#include <cstring>
#include <string>
#include <sys/types.h>
#include <vector>

class TestBase;

/**
 * @brief A data structure used to share progress across a socket
 *
 */
struct s_socket_data {
	size_t id;						 /**< the id of the test */
	char testname[SOCKET_BUFF_SIZE]; /**< the name of the test */
	char args[SOCKET_NARGS]
			 [SOCKET_BUFF_SIZE]; /**< the args passed to the test */
	size_t nargs;				 /**< the number of args in the test */
	char message[SOCKET_MESSAGE_BUFF_SIZE]; /**< a custom message, usually set
											   for errors */
	size_t index;							/**< the index of the subtest */
	bool result;							/**< the result of the test */
	bool crashed;							/**< did the test crashed */
	int crash_value; /**< the signal's code received for the crash */

	s_socket_data();
	s_socket_data(TestBase *, size_t index, bool result,
				  const std::vector<std::tuple<size_t, std::string>> &args,
				  std::string msg = "");
	s_socket_data(int signal);
	~s_socket_data();

  private:
	void zero();
};

typedef struct s_socket_data t_socket_data;

#endif