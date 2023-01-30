#ifndef TESTFRAMEWORK_TEST_ARG_H
#define TESTFRAMEWORK_TEST_ARG_H

#include <qt5/QtWidgets/QLabel>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtWidgets/QHBoxLayout>

#include <string>

#include "testframework/Socket/defines.h"

class TestFrameworkTestArg : public QWidget {
  private:
	t_socket_data socket_data;

    QHBoxLayout *layout;
    QLabel *text;
  public:
	TestFrameworkTestArg(t_socket_data d);
    ~TestFrameworkTestArg();
};

#endif