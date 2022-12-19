#include "Utils/Functions.h"

template <>
std::string toString<const char *>(const char *i)
{
	return (std::string(i));
}
