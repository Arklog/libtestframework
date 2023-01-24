#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QtWidgets>

class MainWindow : public QMainWindow {
  private:
	QMenu *menu_file;
	QMenu *menu_run;
	void setup_widgets();
	void setup_widget_menu();

  public:
	MainWindow();
	~MainWindow();
};

#endif