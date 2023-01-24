#include "Qt/Window/MainWindow.h"

MainWindow::MainWindow() {
	this->resize(400, 400);
	this->setWindowTitle(QApplication::translate("toplevel", "TestFramework"));
	this->setup_widgets();
	this->show();
}

MainWindow::~MainWindow() {
	delete this->menu_file;
	this->close();
}

void MainWindow::setup_widgets() {
	this->setup_widget_menu();
}

void MainWindow::setup_widget_menu() {
	this->menu_file = new QMenu("File");
	this->menu_run = new QMenu("Run");

	menuBar()->addMenu(this->menu_file);
	menuBar()->addMenu(this->menu_run);
}