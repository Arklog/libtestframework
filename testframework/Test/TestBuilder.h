#ifndef TEST_BUILDER_H
#define TEST_BUILDER_H

#include "testframework/Generator/GeneratorBuilder.h"
#include "testframework/Test/Test.h"
#include "testframework/Test/TestBase.h"

namespace TestBuilder {
template <typename... T>
TestBase *create_test(std::string name, std::function<bool(T...)> f,
					  Generator<T> *...);
}

template <typename... T>
TestBase *TestBuilder::create_test(std::string name,
								   std::function<bool(T...)> f,
								   Generator<T> *...gen) {
	return new Test(name, f, GeneratorList<T...>(gen...));
}
#endif