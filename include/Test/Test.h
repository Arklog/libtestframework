#ifndef TEST_H
#define TEST_H

#include <string>
#include <vector>

class Test
{
protected:
	bool _exec;
	bool _result;

public:
	Test();
	virtual ~Test();

	virtual void run() = 0;

	virtual std::vector<std::string> to_string() const;
	virtual std::string get_error() const = 0;
	virtual bool executed() const;
	virtual bool result() const;
};

#endif
