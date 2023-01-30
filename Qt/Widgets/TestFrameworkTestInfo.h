#ifndef TESTFRAMEWORK_TEST_INFO_H
#define TESTFRAMEWORK_TEST_INFO_H

#include <qt5/QtWidgets/QGroupBox>
#include <qt5/QtWidgets/QRadioButton>
#include <qt5/QtWidgets/QVBoxLayout>
#include <qt5/QtWidgets/QWidget>

#include <exception>
#include <iostream>
#include <vector>

#include "Qt/Widgets/TestFrameworkTestArgList.h"
#include "testframework/Global/mutex.h"
#include "testframework/Socket/defines.h"
#include "testframework/testframework/TestFramework.h"

class TestFrameworkTestInfo : public QWidget {
  private:
	int current_test;
	std::vector<TestFrameworkTestArgList *> vec;

	QVBoxLayout *layout;
	QGroupBox *buttons;

	void draw_tests_info();

  public:
	TestFrameworkTestInfo() noexcept;
	~TestFrameworkTestInfo() noexcept;

	/**
	 * @brief Set the current test for which the info should be displayed
	 *
	 * @param test_id
	 */
	void set_test(size_t test_id);

	/**
	 * @brief Add test datas for a test
	 *
	 * @param d
	 */
	void add_test_data(t_socket_data d);

	void init();
};

#endif