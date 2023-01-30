#ifndef TESTFRAMEWORK_TEST_H
#define TESTFRAMEWORK_TEST_H

#include "testframework/Socket/defines.h"
#include "testframework/Test/TestBase.h"

#include <qt5/QtCore/QTimer>
#include <qt5/QtWidgets/QGridLayout>
#include <qt5/QtWidgets/QtWidgets>

class TestFrameworkTest : public QWidget {
  private:
	std::string testname;
	size_t test_id;
	size_t index_max;

	bool finished;

	QTimer *timer;

	QLabel *label;
	QProgressBar *progress;
	QGridLayout *layout;

  protected:
  public:
	TestFrameworkTest(QWidget *parent, const TestBase *test);
	~TestFrameworkTest();

	std::string get_test_name() const;

	void start();
	void stop();
	void incr();
	void process_data(t_socket_data d);
	void update_info();
};

#endif