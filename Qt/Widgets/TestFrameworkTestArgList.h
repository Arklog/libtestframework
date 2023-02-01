#ifndef TESTFRAMEWORK_TEST_ARG_LIST_H
#define TESTFRAMEWORK_TEST_ARG_LIST_H

#include <qt5/QtWidgets/QScrollArea>
#include <qt5/QtWidgets/QVBoxLayout>
#include <qt5/QtWidgets/QWidget>

#include <iostream>
#include <vector>

#include "Qt/Widgets/TestFrameworkTestArg.h"
#include "testframework/Global/mutex.h"
#include "testframework/Socket/defines.h"

class TestFrameworkTestArgList : public QWidget {
  private:
	QVBoxLayout *layout;
	QVBoxLayout *main_layout;
	QWidget *central_widget;
	QScrollArea *scroll;

	std::vector<TestFrameworkTestArg *> vec;
	bool _display_all;

  public:
	TestFrameworkTestArgList();
	~TestFrameworkTestArgList();

	void add_data(t_socket_data d);

	/**
	 * Set if whether or not all test arguments should be shown
	 *
	 * @param display_all if true everything is shown, else only error are shown
	 */
	void display_all(bool display_all);
};

#endif