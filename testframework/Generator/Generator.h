#ifndef GENERATOR_H
#define GENERATOR_H

#include <sys/types.h>

/**
 * @brief A generator's goal is to generate values of any type. Alone this class
 * is useless.
 * @tparam T the type of value that this generator must generate
 */
template <typename T> class Generator {
  private:
  protected:
	size_t index_current;
	size_t index_max;
	T value_current;
	bool finished;

  public:
	Generator();
	Generator(T init_val, size_t max);
	virtual ~Generator();

	/**
	 * @brief Get the current value of the generator.
	 * @return The current value of the generator.
	 */
	T get_current() const;
	/**
	 * @brief Get the next value of the generator.
	 * @return The next value of the generator.
	 */
	T get_next();
	/**
	 * @brief Get the value of the generator at index i.
	 * @param i the index of the value to be generated
	 * @return The value at index i.
	 */
	T get_at(size_t i);

	/**
	 * @brief Get the current index of the generator.
	 * @return The current index of the generator.
	 */
	size_t get_index() const;
	/**
	 * @brief Get the maximum index of the generator.
	 * @return The maximum index of the generator.
	 */
	size_t get_index_max() const;

	/**
	 * @brief Check if the generator is finished.
	 * @return Return true if the generator have finished generating, false
	 * else.
	 */
	bool is_finished() const;

	/**
	 * @brief Generate the next value.
	 */
	virtual void generate_next() = 0;
	/**
	 * @brief Generate the value at index i.
	 * @param i The index of the value to be generated.
	 */
	virtual void generate_at(size_t i);
	/**
	 * @brief Reset the generator.
	 */
	virtual void reset() = 0;

	operator T() const;
};

template <typename T> Generator<T>::Generator() {}

template <typename T>
Generator<T>::Generator(T val, size_t max)
	: index_current(0), index_max(max), value_current(val), finished(false) {}

template <typename T> Generator<T>::~Generator() {}

template <typename T> T Generator<T>::get_current() const {
	return this->current;
}

template <typename T> T Generator<T>::get_next() {
	this->generate_next();
	return this->current;
}

template <typename T> T Generator<T>::get_at(size_t i) {
	this->generate_at(i);
	return this->current;
}

template <typename T> size_t Generator<T>::get_index() const {
	return this->index_current;
}

template <typename T> size_t Generator<T>::get_index_max() const {
	return this->index_max;
}

template <typename T> bool Generator<T>::is_finished() const {
	return this->finished;
}

template <typename T> void Generator<T>::generate_at(size_t i) {
	this->reset();
	while (i--)
		this->generate_next();
}

template <typename T> Generator<T>::operator T() const {
	return this->get_current();
}

#endif