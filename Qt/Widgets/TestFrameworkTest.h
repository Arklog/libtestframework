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

 /**
  * @brief Increment the counter
  * 
  */
	void incr();

	/**
	 * @brief Select this test to be displayed in the test info section
	 * 
	 */
	void select();

	/**
	 * @brief Process some socket_data related to this test
	 * 
	 * @param d 
	 */
	void process_data(t_socket_data d);

	/**
	 * @brief Update the widget
	 * 
	 */
	void update_info();
};

#endif