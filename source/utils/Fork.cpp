//
// Created by pierre on 27/02/23.
//

#include "testframework/utils/Fork.h"
Fork::Fork(const std::function<void()> &child,
		   const std::function<void(pid_t child_pid)> &parent) {
	pid_t pid = fork();

	if (pid < 0) {
		print_error("Fork: could not fork", strerror(errno));
	} else if (!pid) {
		child();
	} else {
		parent(pid);
	}
}
Fork::Fork(const std::function<void()> &child,
		   const std::function<void()> &parent,
		   const std::function<void()> &success,
		   const std::function<void(int sig)> &error,
		   const std::function<void()> &final) {
	pid_t pid = fork();
	int status = 0;

	if (pid < 0) {
		print_error("Fork: could not fork:", strerror(errno));
	} else if (!pid) {
		child();
	} else {
		parent();
		waitpid(pid, &status, 0);
		if (WIFSTOPPED(status)) {
			error(WSTOPSIG(status));
		} else {
			success();
		}
		if (final)
			final();
	}
}