#ifndef OUTPUT_H
#define OUTPUT_H

#include "testframework/Global/mutex.h"
#include <iostream>

template <typename... T> void _print(T... args) {
	((std::cout << " " << args << " "), ...);
}

template <typename... T> void print_info(T... args) {
#ifdef DEBUG
	std::lock_guard<std::mutex> guard(cout_mutex);
	std::cout << "[INFO]:";
	_print(args...);
	std::cout << std::endl;
#endif
}

template <typename... T> void print_error(T... args) {
#ifdef DEBUG
	std::lock_guard<std::mutex> guard(cout_mutex);
	std::cout << "[ERROR]:";
	_print(args...);
	std::cout << std::endl;
#endif
}

#endif