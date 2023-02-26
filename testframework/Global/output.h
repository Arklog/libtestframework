#ifndef OUTPUT_H
#define OUTPUT_H

#include "testframework/Global/mutex.h"
#include <iostream>

template <typename... T> void output_print(T... args) {
	((std::cout << " " << args << " "), ...);
}

template <typename... T> void print_info(T... args) {
#ifdef DEBUG
	std::lock_guard<std::mutex> guard(cout_mutex);
	std::cout << "[INFO] :";
	output_print(args...);
	std::cout << std::endl;
	std::cout.flush();
#endif
}

template <typename... T> void print_error(T... args) {
#ifdef DEBUG
	std::lock_guard<std::mutex> guard(cout_mutex);
	std::cout << "[ERROR]:";
	output_print(args...);
	std::cout << std::endl;
	std::cout.flush();
#endif
}

#endif