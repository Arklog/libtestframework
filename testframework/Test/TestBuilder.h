#ifndef TEST_BUILDER_H
#define TEST_BUILDER_H

#include "testframework/Generator/GeneratorBuilder.h"
#include "testframework/Test/Test.h"
#include "testframework/Test/TestBase.h"
#include <memory>

namespace TestBuilder {
template <typename... T>
std::shared_ptr<TestBase>
create_test(std::string name, std::function<bool(T...)> f, Generator<T> *...);
}

template <typename... T>
std::shared_ptr<TestBase> TestBuilder::create_test(std::string name,
												   std::function<bool(T...)> f,
												   Generator<T> *...gen) {
	return std::make_shared<Test<T...>>(name, f,
										new GeneratorList<T...>(gen...));
}
#endif