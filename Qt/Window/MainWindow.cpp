#include "Qt/Window/MainWindow.h"
#include "testframework/Socket/Server.h"
#include "testframework/Socket/defines.h"
#include "testframework/Test/TestManager.h"
#include "testframework/testframework/TestFramework.h"

MainWindow::MainWindow() {
	this->resize(600, 800);
	this->setWindowTitle(QApplication::translate("toplevel", "TestFramework"));
	this->test_widgets = std::vector<TestFrameworkTest *>();
	this->timer = new QTimer();
	connect(this->timer, &QTimer::timeout, this, &MainWindow::update_tests);
	this->setup_widgets();
	this->show();
}

MainWindow::~MainWindow() {
	delete this->menu_file;
	delete this->menu_run;
	delete this->central_widget;

	TestFramework::get_instance()->stop();
}

void MainWindow::setup_widgets() {
	this->setup_widget_menu();

	this->grid = new QGridLayout();
	this->test_layout = new QVBoxLayout();
	this->info_layout = new QVBoxLayout();

	this->info_layout->addWidget(new TestFrameworkTestInfo(0));

	this->grid->addLayout(this->test_layout, 0, 0);
	this->grid->addLayout(this->info_layout, 0, 1);

	this->central_widget = new QWidget();
	this->central_widget->setLayout(this->grid);
	this->setCentralWidget(this->central_widget);
}

void MainWindow::setup_widget_menu() {
	this->menu_file = new QMenu("File");
	this->menu_run = new QMenu("Run");

	this->setup_widget_menu_file();
	this->setup_widget_menu_run();

	menuBar()->addMenu(this->menu_file);
	menuBar()->addMenu(this->menu_run);
}

void MainWindow::setup_widget_menu_file() {
	QAction *action;

	action = new QAction("Open");
	connect(action, &QAction::triggered, this, &MainWindow::open_lib);
	this->menu_file->addAction(action);
}

void MainWindow::setup_widget_menu_run() {
	QAction *action;

	action = new QAction("Run");
	connect(action, &QAction::triggered, this, &MainWindow::run_tests);
	this->menu_run->addAction(action);
}

void MainWindow::open_lib() {
	QString filename = QFileDialog::getOpenFileName(
		this, tr("Open file"), QString("~/"), tr("Shared library (*.so)"));
	TestFramework::get_instance()->new_project(filename.toStdString());

	auto v = TestFramework::get_instance()->get_test_manager()->get_tests();
	TestFrameworkTest *w;
	for (auto i : v) {
		w = new TestFrameworkTest(nullptr, i);
		this->test_widgets.push_back(w);
		this->test_layout->addWidget(w);
	}
	this->update();
}

void MainWindow::run_tests() {
	pid_t pid;
	int status;

#ifdef TESTFRAMEWORK_NOFORK
	TestFramework::get_instance()->get_test_manager()->execute_tests();
#else
	pid = TestFramework::get_instance()->get_test_manager()->fork_run();
	if (pid == 0) {
		TestFramework::get_instance()->stop();
		_Exit(0);
	}
	this->test_run_thread = std::thread([this, pid, &status]() {
		waitpid(pid, &status, 0);
		std::lock_guard<std::mutex> guard(this->finished_mutex);
		this->finished = true;
	});
	this->timer->start(100);

#ifdef DEBUG
	if (status) {
		std::cout << "[ERROR]: child process failed error code " << status
				  << std::endl;
	} else {
		std::cout << "[INFO]: child process finished successfully\n";
	}
#endif
#endif
}

void MainWindow::update_tests() {
	std::vector<t_socket_data> v;

	this->finished_mutex.lock();
	if (this->finished) {
		this->timer->stop();
		this->test_run_thread.join();
	}
	this->finished_mutex.unlock();
	v = TestFramework::get_instance()->get_server_socket()->get_socket_datas();
	for (auto d : v)
		this->test_widgets.at(d.id)->process_data(d);
}