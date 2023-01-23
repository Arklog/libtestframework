#ifndef GENERATOR_BUILDER_H
#define GENERATOR_BUILDER_H

#include <vector>
#include "testframework/Generator/GeneratorRange.h"

template <typename T>
class Generator;

namespace GeneratorBuilder {
	template <typename T>
	Generator<T> *create_generator(std::vector<T> vec);
}

template <typename T>
Generator<T> *GeneratorBuilder::create_generator(std::vector<T> vec)
{
	return new GeneratorRange<T>(vec);
}

#endif