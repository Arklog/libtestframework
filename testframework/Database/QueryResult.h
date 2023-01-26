#ifndef QUERY_RESULT_H
#define QUERY_RESULT_H

#include <string>
#include <vector>

typedef struct s_query_arg {
	int id;
	size_t pos;
	std::string value;
} t_arg;

typedef struct s_query_result {
	int id;
	int index;
	bool result;
	std::vector<t_arg> args;
} t_result;

typedef struct s_query_test {
	int id;
	std::string name;
	std::vector<t_result> results;
} t_test;

#endif