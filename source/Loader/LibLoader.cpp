#include "testframework/Loader/LibLoader.h"
#include "testframework/Test/TestManager.h"
#include "testframework/testframework/TestFramework.h"

LibLoader::LibLoader() : handle(nullptr), f(nullptr) {}

LibLoader::~LibLoader() { this->close(); }

void LibLoader::load(std::string name) {
	char *error;
	int code;

	handle = nullptr;
	f = nullptr;
	this->handle = dlopen(name.c_str(), RTLD_NOW);
	code = errno;
	if (!this->handle) {
		print_error("LibLoader:", name, ":", strerror(code));
		return;
	} else {
		print_info("LibLoader:", name, "loaded");
	}
	*(void **)(&this->f) = dlsym(this->handle, "testframework_setup_tests");
	if ((error = dlerror())) {
		print_error("LibLoader:", name, ":", error);
	} else {
		print_info("LibLoader: entry point found");
	}
}

void LibLoader::load_tests() {
	if (handle && f) {
		this->f(TestFramework::get_instance());
		print_info("LibLoader: test loaded");
	} else {
		print_error("LibLoader: could not load tests");
	}
}

void LibLoader::close() {
	print_info("LibLoader: closing library");
	if (this->handle)
		dlclose(this->handle);
	this->f = nullptr;
	this->handle = nullptr;
}