#include <cstdio>
#include <iostream>
#include "TestFuncCmp.h"
#include "TestSuite.h"
#include "TestManager.h"
#include "MainWindow.h"

int main()
{
	std::vector<Test *> v = std::vector<Test *>();
	TestSuite			*suite;
	Test				*t;

	for (int i = 0; i < 10; ++i)
	{
		t = new TestFuncCmp<int, const char *, int>(printf, printf, "%d", 5);
		v.push_back(t);
	}
	suite = new TestSuite("printf", v);

	TestManager::get()->add_test(suite);

	MainWindow w = MainWindow();
	w.display_loop();

	endwin();
}
