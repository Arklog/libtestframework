#include "Generator/GeneratorBuilder.h"
#include <cstdio>
#include <string>

template <typename T>
bool testGeneratorNext(std::string name, std::vector<T> vec,
					   Generator<T> *gen) {
	size_t index;
	index = 0;

	gen->reset();
	for (auto i : vec) {
		if (i != gen->get_current()) {
			printf("%-10s%-30.30s at (%ld, %ld)\n", "[FAIL next]", name.c_str(),
				   index, gen->get_index());
			return false;
		}
		++index;
		gen->generate_next();
	}
	printf("%-10s%-30.30s\n", "[OK next]", name.c_str());
	return (true);
}

template <typename T>
bool testGeneratorAt(std::string name, std::vector<T> vec, Generator<T> *gen) {
	size_t i;

	i = 0;
	gen->reset();
	while (i < vec.size()) {
		if (vec.at(i) != gen->get_at(i)) {
			printf("%-10s%-30.30s at (%ld, %ld)\n", "[FAIL at]", name.c_str(),
				   i, gen->get_index());
			return (false);
		}
		++i;
	}
	printf("%-10s%-30.30s\n", "[OK at]", name.c_str());
	return (true);
}

template <typename T>
bool testGenerator(std::string name, std::vector<T> vec, Generator<T> *gen) {
	bool result;

	result = true;
	result &= testGeneratorNext<T>(name, vec, gen);
	result &= testGeneratorAt<T>(name, vec, gen);

	delete gen;
	return result;
}

int main() {
	testGenerator<int>("generator int", {0, 1, 2, 3},
					   GeneratorBuilder::create_generator<int>({0, 1, 2, 3}));
	return (0);
}