#ifndef GENERATOR_RANGE_H
#define GENERATOR_RANGE_H

#include "testframework/Generator/Generator.h"
#include <vector>

template <typename T> class GeneratorArray : public Generator<T> {
  private:
	std::vector<T> vec;

  public:
	GeneratorArray(std::vector<T> elements);
	~GeneratorArray();

	void generate_next() override;
	void generate_at(size_t i) override;
	void reset() override;
};

template <typename T>
GeneratorArray<T>::GeneratorArray(std::vector<T> elements)
	: Generator<T>(elements.at(0), elements.size() - 1), vec(elements) {}

template <typename T> GeneratorArray<T>::~GeneratorArray() = default;

template <typename T> void GeneratorArray<T>::generate_next() {
	if (this->get_index() == this->get_index_max())
		return;
	this->value_current = this->vec.at(++this->index_current);
	if (this->get_index() == this->get_index_max())
		this->finished = true;
}

template <typename T> void GeneratorArray<T>::generate_at(size_t i) {
	if (i > this->get_index_max())
		return;
	this->index_current = i;
	this->value_current = this->vec.at(i);
	if (this->get_index() == this->get_index_max())
		this->finished = true;
}

template <typename T> void GeneratorArray<T>::reset() {
	this->index_current = 0;
	this->value_current = this->vec.at(0);
	this->finished = (this->index_current != this->index_max) ? false : true;
}

#endif