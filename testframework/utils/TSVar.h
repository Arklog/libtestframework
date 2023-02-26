//
// Created by pierre on 25/02/23.
//

#ifndef LIBTESTFRAMEWORK_TSVAR_H
#define LIBTESTFRAMEWORK_TSVAR_H

#include <mutex>

template <typename T> class TSVar {
  private:
	std::mutex _mutex;
	T var;

  public:
	TSVar();
	explicit TSVar(T var);

	T get();
};

template <typename T> TSVar<T>::TSVar() : var() {}

template <typename T> TSVar<T>::TSVar(T var) : var(var) {}

template <typename T> T TSVar<T>::get() {
	std::lock_guard<std::mutex> lock(_mutex);
	return (var);
}

#endif // LIBTESTFRAMEWORK_TSVAR_H
