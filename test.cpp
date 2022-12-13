#include <cstdio>
#include <iostream>
#include "TestFuncCmp.h"
#include "TestFuncCmpGen.h"
#include "TestSuite.h"
#include "TestManager.h"
#include "MainWindow.h"
#include "GeneratorRange.h"
#include <cctype>

int main()
{
	std::vector<Test *> v = std::vector<Test *>();
	TestSuite			*suite;
	Test				*t;

	// Test TestFuncCmp
	for (int i = 0; i < 10; ++i)
	{
		t = new TestFuncCmp<int, const char *, int>(printf, printf, "%d", 5);
		v.push_back(t);
	}
	suite = new TestSuite("printf", v);
	TestManager::get()->add_test(suite);

	// Test TestFuncCmpGen
	TestFuncCmpGen<int, int> test = TestFuncCmpGen<int, int>(std::isprint, std::isprint, 
		new GeneratorRange<int>(0, 255));

	MainWindow w = MainWindow();
	w.display_loop();

	endwin();
}
