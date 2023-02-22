//
// Created by pierre on 22/02/23.
//

#ifndef LIBTESTFRAMEWORK_THREADWRAPPER_H
#define LIBTESTFRAMEWORK_THREADWRAPPER_H

#include <functional>
#include <string>
#include <thread>

#include "testframework/Global/output.h"

class ThreadWrapper {
  private:
	std::thread th;
	std::string name;

  public:
	ThreadWrapper();
	explicit ThreadWrapper(std::function<void()> l, std::string name = "");
	~ThreadWrapper();

	ThreadWrapper &operator=(ThreadWrapper a);
};

#endif // LIBTESTFRAMEWORK_THREADWRAPPER_H
