#ifndef TESTFRAMEWORK_TEST_INFO_H
#define TESTFRAMEWORK_TEST_INFO_H

#include <qt5/QtWidgets/QWidget>
#include <qt5/QtWidgets/QRadioButton>
#include <qt5/QtWidgets/QGroupBox>
#include <qt5/QtWidgets/QVBoxLayout>

#include <vector>

#include "Qt/Widgets/TestFrameworkTestArg.h"
#include "testframework/Socket/defines.h"

class TestFrameworkTestInfo : public QWidget {
  private:
	static int current_test;
	static std::vector<std::vector<t_socket_data>> socket_datas;

	QVBoxLayout *layout;
	QGroupBox *buttons;

	public:
	TestFrameworkTestInfo(size_t testnumber);
	~TestFrameworkTestInfo();

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

	/**
	 * @brief Reset the widget, should be called each times a new test start
	 * 
	 */
	void clear();
};

#endif