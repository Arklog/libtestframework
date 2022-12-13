#ifndef GENERATORRANGE_H
#define GENERATORRANGE_H

#include "Generator.h"

template <typename T>
class GeneratorRange : public Generator
{
private:
	T _min;
	T _max;
	T _cur;

public:
	GeneratorRange<T>(T min, T max);
	~GeneratorRange();

	bool finished() const;
	T generate();
	std::size_t size() const;
	std::size_t current() const;
	void reset();
};

template <typename T>
GeneratorRange<T>::GeneratorRange(T min, T max) : _min(min), _max(max), _cur(min) {}

template <typename T>
GeneratorRange<T>::~GeneratorRange() {}

template <typename T>
bool GeneratorRange<T>::finished() const
{
	return (this->_cur == this->_max);
}

template <typename T>
T GeneratorRange<T>::generate()
{
	if (this->finished())
		this->reset();
	return (this->_cur++);
}

template <typename T>
std::size_t GeneratorRange<T>::size() const
{
	return (this->_max - this->_min);
}

template <typename T>
std::size_t GeneratorRange<T>::current() const
{
	return (this->_cur - this->_min);
}

template <typename T>
void GeneratorRange<T>::reset()
{
	this->_cur = this->_min;
}
#endif