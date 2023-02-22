//
// Created by pierre on 22/02/23.
//

#include "testframework/utils/ThreadWrapper.h"
ThreadWrapper::ThreadWrapper() = default;

ThreadWrapper::ThreadWrapper(std::function<void()> l, std::string name)
	: th(std::thread(l)), name(name) {
	print_info("ThreadWrapper: starting", name);
}

ThreadWrapper::~ThreadWrapper() {
	try {
		if (th.joinable()) {
			th.join();
			print_info("ThreadWrapper: thread joined");
		}
	} catch (std::exception &e) {
		print_error("ThreadWrapper:", e.what());
	}
}

ThreadWrapper &ThreadWrapper::operator=(ThreadWrapper a) {
	name = a.name;
	th = std::move(a.th);
	return *this;
}
