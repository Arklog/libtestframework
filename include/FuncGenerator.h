#ifndef FUNCGENERATOR_H
# define FUNCGENERATOR_H

# include <functional>
# include "Generator.h"

template <typename T>
class FuncGenerator: public Generator<T>
{
	private:
		std::function<T(bool)>		_fun;
		std::size_t					_size;
		std::size_t					_i;

	public:
		/**
		 * Constructor
		 *
		 * @param f		the generator function, accept a boolean, on true it will
		 * 				reset its static variables, this allow to run a generator
		 * 				multiple time
		 * @param max	the maximum number of run of a generator function, if this
		 * 				number is reached the function will be reset.
		 */
		FuncGenerator<T>(std::function<T(bool)> f, std::size_t max);
		~FuncGenerator<T>();

		T			generate() override;
		std::size_t	size() const override;
		std::size_t	current() const override;
		bool		finished() const override;
		void		reset() override;
};

template <typename T>
FuncGenerator<T>::FuncGenerator(std::function<T(bool)> f, std::size_t max):
	_fun(f), _size(max)
{
}

template <typename T>
FuncGenerator<T>::~FuncGenerator()
{
}

template <typename T>
T FuncGenerator<T>::generate()
{
	if (++(this->_i) >= this->_size)
		this->_fun(true); //reset generator
	return (this->_fun(false));
}

template <typename T>
bool	FuncGenerator<T>::finished() const
{
	return (this->_i == this->_size);
}

template <typename T>
std::size_t	FuncGenerator<T>::size() const
{
	return (this->_size);
}

template <typename T>
std::size_t	FuncGenerator<T>::current() const
{
	return (this->_i);
}

template <typename T>
void	FuncGenerator<T>::reset()
{
	this->_fun(true);
	this->_i = 0;
}
#endif
