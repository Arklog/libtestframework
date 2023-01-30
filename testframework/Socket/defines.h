#ifndef SOCKET_DEFINES_H
#define SOCKET_DEFINES_H

#ifndef SOCKET_BUFF_SIZE
#define SOCKET_BUFF_SIZE 256
#endif

#ifndef SOCKET_NARGS
#define SOCKET_NARGS 5
#endif

#include <sys/types.h>

/**
 * @brief A data structure used to share progress accross a socket
 *
 */
typedef struct s_socket_data {
	size_t id;
	char testname[SOCKET_BUFF_SIZE];
	char args[SOCKET_NARGS][SOCKET_BUFF_SIZE];
	int index;
	int nargs;
	bool result;
} t_socket_data;

#endif