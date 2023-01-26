#include "Qt/Window/MainWindow.h"
#include "testframework/testframework/TestFramework.h"

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
	QAction *action;
	this->menu_file = new QMenu("File");
	this->menu_run = new QMenu("Run");

	action = new QAction("Open");
	connect(action, &QAction::triggered, this, &MainWindow::open_lib);
	this->menu_file->addAction(action);

	menuBar()->addMenu(this->menu_file);
	menuBar()->addMenu(this->menu_run);
}

void MainWindow::open_lib()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open file"), QString("~/"), tr("Shared library (*.so)"));
	TestFramework::get_instance()->new_project(filename.toStdString());
}