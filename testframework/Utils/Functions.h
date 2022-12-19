#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

template <typename T>
std::string toString(T i)
{
	return (std::to_string(i));
}

template <>
std::string toString<const char *>(const char *str);

#endif