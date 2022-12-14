#ifndef TESTSUITE_H
# define TESTSUITE_H

# include <vector>
# include <string>
# include <algorithm>
# include "Test/Test.h"

class TestSuite: public Test
{
	private:
		std::string			_name;
		std::vector<Test *>	_tests;

	public:
		TestSuite(std::string name);
		TestSuite(std::string name, std::vector<Test *> tests);
		~TestSuite();

		/**
		 * Run the first non run test on the list
		 */
		void		run() override;

		/**
		 * Convert the current state of the test suite into string,
		 * each string in the vector correspond to a line
		 *
		 * @return		the current state of the suite
		 */
		std::vector<std::string>	to_string() const override;

		/**
		 * Generate the failed test backlog
		 *
		 * @return		the errors
		 */
		std::string	get_error() const override;

		/**
		 * Get the name of this test suite
		 *
		 * @return		this test suite identifier
		 */
		std::string	name() const;

		/**
		 * The result of this test suite, must be called after the tests are done
		 * executing.
		 *
		 * @return		the result of the test suite execution, true if all tests
		 * 				passed, false else.
		 */
		bool		result() const override;

		/**
		 * Whether or not the test suite have fully been executed
		 *
		 * @return		true if each test have been executed, false else
		 */
		bool		executed() const override;

		size_t		ntests() const;
		size_t		nexecuted() const;
};
#endif
