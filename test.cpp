#include <cstdio>
#include <iostream>
#include "Test/TestFuncCmpGen.h"
#include "Test/TestSuite.h"
#include "Test/TestManager.h"
#include "Gui/MainWindow.h"
#include "Generator/GeneratorRange.h"
#include "Utils/Functions.h"
#include <cctype>

int main()
{
	std::vector<Test *> v = std::vector<Test *>();
	TestSuite			*suite;
	Test				*t;

	// Test TestFuncCmp
	suite = new TestSuite("printf");
	for (int i = 0; i < 10; ++i)
	{
		t = new TestFuncCmp<int, const char *, int>(printf, printf, "printf: %d\n", 5);
		suite->add_test(t);
	}
	TestManager::get()->add_test(suite);


	// Test TestFuncCmpGen
	std::function<int(int)> f = [](int i) {
		return std::isprint(i);
	};
	t = new TestFuncCmpGen(f, f, new GeneratorList<int>(new GeneratorRange<int>(0, 0xffff)));
	suite = new TestSuite("isprint");
	suite->add_test(t);
	TestManager::get()->add_test(suite);
	t = new TestFuncCmpGen(f, f, new GeneratorList<int>(new GeneratorRange<int>(0, 0xffff)));
	suite = new TestSuite("isprint");
	suite->add_test(t);
	TestManager::get()->add_test(suite);
	t = new TestFuncCmpGen(f, f, new GeneratorList<int>(new GeneratorRange<int>(0, 0xffff)));
	suite = new TestSuite("isprint");
	suite->add_test(t);
	TestManager::get()->add_test(suite);
	t = new TestFuncCmpGen(f, f, new GeneratorList<int>(new GeneratorRange<int>(0, 0xffff)));
	suite = new TestSuite("isprint");
	suite->add_test(t);
	TestManager::get()->add_test(suite);
	t = new TestFuncCmpGen(f, f, new GeneratorList<int>(new GeneratorRange<int>(0, 0xffff)));
	suite = new TestSuite("isprint");
	suite->add_test(t);
	TestManager::get()->add_test(suite);
	t = new TestFuncCmpGen(f, f, new GeneratorList<int>(new GeneratorRange<int>(0, 0xffff)));
	suite = new TestSuite("isprint");
	suite->add_test(t);
	TestManager::get()->add_test(suite);
	t = new TestFuncCmpGen(f, f, new GeneratorList<int>(new GeneratorRange<int>(0, 0xffff)));
	suite = new TestSuite("isprint");
	suite->add_test(t);
	TestManager::get()->add_test(suite);
	t = new TestFuncCmpGen(f, f, new GeneratorList<int>(new GeneratorRange<int>(0, 0xffff)));
	suite = new TestSuite("isprint");
	suite->add_test(t);
	TestManager::get()->add_test(suite);
	t = new TestFuncCmpGen(f, f, new GeneratorList<int>(new GeneratorRange<int>(0, 0xffff)));
	suite = new TestSuite("isprint");
	suite->add_test(t);
	TestManager::get()->add_test(suite);

	MainWindow w = MainWindow();
	w.display_loop();

	endwin();
}
