#ifndef GENERATOR_RANGE_H
#define GENERATOR_RANGE_H

#include "Generator.h"
#include <vector>

template <typename T> class GeneratorRange : public Generator<T> {
  private:
	std::vector<T> vec;

  public:
	GeneratorRange(std::vector<T> elements);
	~GeneratorRange();

	virtual void generate_next() override;
	virtual void generate_at(size_t i) override;
	virtual void reset() override;
};

template <typename T>
GeneratorRange<T>::GeneratorRange(std::vector<T> elements)
	: Generator<T>(elements.at(0), elements.size() - 1), vec(elements) {}

template <typename T> GeneratorRange<T>::~GeneratorRange() {}

template <typename T>
void GeneratorRange<T>::generate_next()
{
	if (this->get_index() == this->get_index_max())
		return;
	this->value_current = this->vec.at(++this->index_current);
	if (this->get_index() == this->get_index_max())
		this->finished = true;
}

template <typename T>
void GeneratorRange<T>::generate_at(size_t i)
{
	if (i > this->get_index_max())
		return;
	this->index_current = i;
	this->value_current = this->vec.at(i);
	if (this->get_index() == this->get_index_max())
		this->finished = true;
}

template <typename T> void GeneratorRange<T>::reset() {
	this->index_current = 0;
	this->value_current = this->vec.at(0);
	this->finished = (this->index_current != this->index_max) ? false : true;
}

#endif