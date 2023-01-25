#include "testframework/Database/Database.h"
#include "testframework/testframework/TestFramework.h"

int main()
{
	TestFramework::get_instance()->init("std::string project_name");
	Database db;
	db.create();
	db.add_test("testname");
	return 0;
}