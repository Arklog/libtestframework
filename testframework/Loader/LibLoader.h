#ifndef LIBLOADER_H
#define LIBLOADER_H

#include <cstring>
#include <dlfcn.h>
#include <functional>
#include <iostream>
#include <string>

#include "testframework/Test/TestBase.h"

class TestFramework;

class LibLoader {
  private:
	void *handle;
	std::vector<TestBase *> (*f)(TestFramework *);

  public:
	LibLoader();
	~LibLoader();

	void load(std::string name);
	void load_tests();
	void close();
};

#endif