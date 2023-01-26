#include "testframework/Database/Database.h"
#include "testframework/testframework/TestFramework.h"

int main()
{
	TestFramework::get_instance()->init("std::string project_name");
	return 0;
}