#include "testframework/Generator/GeneratorBuilder.h"
#include "testframework/Test/TestBuilder.h"
#include "testframework/Test/TestManager.h"
#include "testframework/testframework/TestFramework.h"
#include "testframework/Test/TestManager.h"

extern "C" void testframework_setup_tests(TestFramework *framework) {
	TestManager *manager;
	std::vector<TestBase *> v;

	if (!framework)
		return ;
	TestFramework::set_instance(framework);
	v.push_back(TestBuilder::create_test(
		"test", std::function<bool(int)>([](int) { return true; }),
		GeneratorBuilder::create_generator<int>({0, 1, 2})));

	TestFramework::get_instance()->get_test_manager()->add_tests(v);
}