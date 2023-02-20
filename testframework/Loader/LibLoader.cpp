#include "Loader/LibLoader.h"
#include "Test/TestManager.h"
#include "testframework/TestFramework.h"

LibLoader::LibLoader() : handle(nullptr), f(nullptr) {}

LibLoader::~LibLoader() { this->close(); }

void LibLoader::load(std::string name) {
	char *error;
	int code;

	this->handle = dlopen(name.c_str(), RTLD_NOW);
	code = errno;
	if (!this->handle) {
		std::cout << "[ERROR]: could not load " << name << std::endl
				  << strerror(code) << std::endl;
		return;
	}
	*(void **)(&this->f) = dlsym(this->handle, "testframework_setup_tests");
	if ((error = dlerror())) {
		std::cout << "[ERROR]: " << error << std::endl;
	}
}

void LibLoader::load_tests() {
	if (this->handle)
		this->f(TestFramework::get_instance());
}

void LibLoader::close() {
	dlclose(this->handle);
	this->f = nullptr;
	this->handle = nullptr;
}