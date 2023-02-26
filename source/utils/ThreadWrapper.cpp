//
// Created by pierre on 22/02/23.
//

#include "testframework/utils/ThreadWrapper.h"
ThreadWrapper::ThreadWrapper() : th(), l(), name(){};

ThreadWrapper::ThreadWrapper(std::function<void()> l, std::string name)
	: th(), l(l), name(name) {
	newThread(l, name);
}

ThreadWrapper::~ThreadWrapper() { join(); }

void ThreadWrapper::newThread(std::function<void()> _l, std::string _name) {
	try {
		join();
		name = _name;
		l = _l;
		th = std::thread(_l);
		print_info("ThreadWrapper: thread created", name);
		updateName();
	} catch (std::exception &e) {
		print_error("ThreadWrapper: could not create new thread");
	}
}

void ThreadWrapper::updateName() {
	if (pthread_setname_np(th.native_handle(), name.c_str()))
		print_error("ThreadWrapper: could not set name for", name);
	else
		print_info("ThreadWrapper: name set for", name);
}
void ThreadWrapper::join() {
	try {
		print_info("ThreadWrapper:", name, "try join in",
				   std::this_thread::get_id());
		if (th.joinable()) {
			th.join();
		}
		print_info("ThreadWrapper:", name, "joined");
	} catch (std::exception &e) {
		print_error("ThreadWrapper:", name, ":", e.what());
	}
}
