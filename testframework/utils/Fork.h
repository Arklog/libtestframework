//
// Created by pierre on 27/02/23.
//

#ifndef LIBTESTFRAMEWORK_FORK_H
#define LIBTESTFRAMEWORK_FORK_H

#include "testframework/Global/output.h"
#include <cerrno>
#include <cstring>
#include <functional>
#include <sys/wait.h>
#include <unistd.h>

class Fork {
  public:
	explicit Fork(const std::function<void()> &child,
				  const std::function<void(pid_t child_pid)> &parent);
	explicit Fork(const std::function<void()> &child,
				  const std::function<void()> &parent,
				  const std::function<void()> &success,
				  const std::function<void(int sig)> &error,
				  const std::function<void()> &final = nullptr);
};

#endif // LIBTESTFRAMEWORK_FORK_H
