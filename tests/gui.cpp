#include "testframework/Generator/GeneratorBuilder.h"
#include "testframework/Test/TestBuilder.h"
#include "testframework/Test/TestManager.h"
#include "testframework/testframework/TestFramework.h"

#include <cctype>

extern "C" void testframework_setup_tests(TestFramework *framework) {
	TestManager *manager;
	std::vector<TestBase *> v;

	std::vector<int> t;
	for (int i = 0; i <= 0xffff; ++i)
		t.push_back(i);

	if (!framework)
		return;
	TestFramework::set_instance(framework);
	v.push_back(TestBuilder::create_test(
		"test", std::function<bool(int)>([](int i) { return isalpha(i); }),
		GeneratorBuilder::create_generator<int>(t)));
	v.push_back(TestBuilder::create_test(
		"test2", std::function<bool(int)>([](int) { return true; }),
		GeneratorBuilder::create_generator<int>(t)));

	TestFramework::get_instance()->get_test_manager()->add_tests(v);
}