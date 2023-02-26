//
// Created by pierre on 25/02/23.
//
#include "testframework/Global/output.h"
#include "testframework/utils/ThreadWrapper.h"

int main() {
	ThreadWrapper t1, t2;

	t1.newThread(
		[]() {
			print_info("wait");
			sleep(2);
			for (int i = 0; i < 1000; ++i)
				print_info("t1");
		},
		"t1");
	t2.newThread(
		[]() {
			print_info("wait");
			sleep(2);
			for (int i = 0; i < 10; ++i)
				print_info("t2");
		},
		"t2");
}