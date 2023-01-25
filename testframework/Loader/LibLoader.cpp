#include "testframework/Loader/LibLoader.h"

LibLoader::LibLoader() : handle(nullptr), f(nullptr) {}

LibLoader::~LibLoader() { this->close(); }

void LibLoader::load(std::string name) {
	this->handle = dlopen(name.c_str(), 0);
	if (!this->handle)
	{
		return ;
	}
	*(void **)(&this->f) = dlsym(this->handle, "testframework_setup_tests");
}

void LibLoader::load_tests()
{
	this->f();
}

void LibLoader::close()
{
	dlclose(this->handle);
	this->f = nullptr;
	this->handle = nullptr;
}