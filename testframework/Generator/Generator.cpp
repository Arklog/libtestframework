export module Generator;

#include <sys/types.h>

export template <typename T> class Generator {
  private:
  protected:
	size_t index_current;
	size_t index_max;
	T value_current;

  public:
	Generator();
	virtual ~Generator();

	T get_current() const;
	T get_next();
	T get_at(size_t i);

	size_t get_index() const;
	size_t get_index_max() const;

	virtual void generate_next() = 0;
	virtual void generate_at(size_t i);
	virtual void reset() = 0;
};

export template <typename T> Generator<T>::Generator() {}

export template <typename T> Generator<T>::~Generator() {}

export template <typename T> T Generator<T>::get_current() const {
	return this->current;
}

export template <typename T> T Generator<T>::get_next() {
	this->generate_next();
	return this->current;
}

export template <typename T> T Generator<T>::get_at(size_t i) {
	this->generate_at(i);
	return this->current;
}

export template <typename T> size_t Generator<T>::get_index() const {
	return this->index_current;
}

export template <typename T> size_t Generator<T>::get_index_max() const {
	return this->index_max;
}

export template <typename T> void Generator<T>::generate_at(size_t i) {
	this->reset();
	while (i--)
		this->generate_next();
}