#ifndef TESTFRAMEWORK_TEST_H
#define TESTFRAMEWORK_TEST_H

#include "testframework/Socket/defines.h"
#include "testframework/Test/TestBase.h"

#include <qt5/QtCore/QTimer>
#include <qt5/QtWidgets/QGridLayout>
#include <qt5/QtWidgets/QtWidgets>

#include <functional>

class TestFrameworkTestInfo;

class TestFrameworkTest : public QWidget {
	Q_OBJECT
  private:
	std::string testname;
	size_t test_id;
	size_t index_max;

	static std::function<void(int)> on_click_callback;
	bool finished;

	QTimer *timer;

	QLabel *label;

	QProgressBar *progress;
	QGridLayout *layout;

  protected:
  public:
	TestFrameworkTest(QWidget *parent, const TestBase *test);
	virtual ~TestFrameworkTest();
	std::string get_test_name() const;

	static TestFrameworkTestInfo *info_ptr;

	/**
	 * @brief Increment the counter
	 *
	 */
	void incr();

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

  signals:
	void mousePressEvent(QMouseEvent *event) override;

  public slots:
	/**
	 * @brief Select this test to be displayed in the test info section
	 *
	 */
	void select();
};

#endif