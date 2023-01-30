#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <sys/wait.h>

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QtWidgets>

#include "Qt/Widgets/TestFrameworkTest.h"
#include "Qt/Widgets/TestFrameworkTestInfo.h"

class MainWindow : public QMainWindow {
  private:
	/**
	 * @brief File menu
	 */
	QMenu *menu_file;

	/**
	 * @brief Run menu
	 */
	QMenu *menu_run;

	/**
	 * @brief Main layout
	 */
	QGridLayout *grid;

	/**
	 * @brief Leftmost layout
	 */
	QVBoxLayout *test_layout;

	/**
	 * @brief Rightmost layout
	 */
	QVBoxLayout *info_layout;

	QWidget *central_widget;

	QTimer *timer;

	std::vector<TestFrameworkTest *> test_widgets;

	std::thread test_run_thread;
	std::mutex finished_mutex;
	bool finished;

	void setup_widgets();
	void setup_widget_menu();
	void setup_widget_menu_file();
	void setup_widget_menu_run();

  public:
	MainWindow();
	~MainWindow();

	void open_lib();

	void run_tests();

	void update_tests();
};

#endif