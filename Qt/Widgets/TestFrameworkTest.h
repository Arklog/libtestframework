#ifndef TESTFRAMEWORK_TEST_H
#define TESTFRAMEWORK_TEST_H

#include "testframework/Test/TestBase.h"
#include <qt5/QtWidgets/QGridLayout>
#include <qt5/QtWidgets/QtWidgets>

class TestFrameworkTest : public QWidget {
  private:
	std::string testname;

	QLabel *label;
	QProgressBar *progress;
	QGridLayout *layout;

  protected:
  public:
	TestFrameworkTest(QWidget *parent, const TestBase *test);
	~TestFrameworkTest();
};

#endif