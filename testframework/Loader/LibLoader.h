#ifndef LIBLOADER_H
#define LIBLOADER_H

#include <dlfcn.h>
#include <functional>
#include <string>
class LibLoader {
  private:
	void *handle;
	void (*f)();

  public:
	LibLoader();
	~LibLoader();

	void load(std::string name);
	void load_tests();
	void close();
};

#endif