//
// Created by pierre on 22/02/23.
//

#ifndef LIBTESTFRAMEWORK_THREADWRAPPER_H
#define LIBTESTFRAMEWORK_THREADWRAPPER_H

#include <functional>
#include <pthread.h>
#include <string>
#include <thread>

#include "testframework/Global/output.h"

class ThreadWrapper {
  private:
	std::thread th;
	std::function<void()> l;

	void updateName();

  private:
	std::string name;

  public:
	ThreadWrapper();
	explicit ThreadWrapper(std::function<void()> l, std::string name = "");
	~ThreadWrapper();

	void newThread(std::function<void()> _l, std::string _name = "");

	void join();
};

#endif // LIBTESTFRAMEWORK_THREADWRAPPER_H
