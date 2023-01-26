#include "Qt/Window/MainWindow.h"
#include "testframework/Test/TestManager.h"
#include "testframework/testframework/TestFramework.h"

MainWindow::MainWindow() {
	this->resize(400, 400);
	this->setWindowTitle(QApplication::translate("toplevel", "TestFramework"));
	this->test_widgets = std::vector<TestFrameworkTest *>();
	this->setup_widgets();
	this->show();
}

MainWindow::~MainWindow() {
	delete this->menu_file;
	delete this->menu_run;
	delete this->central_widget;

	this->close();
}

void MainWindow::setup_widgets() {
	this->setup_widget_menu();
	this->grid = new QGridLayout();
	this->test_layout = new QVBoxLayout();
	this->grid->addLayout(this->test_layout, 0, 0);
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

	action = new QAction("Open db");
	connect(action, &QAction::triggered, []() {
		char *args[] = {strdup("sqlitebrowser"),
						strdup(TestFramework::get_instance()
								   ->get_database()
								   ->get_db_name()
								   .c_str()),
						NULL};

		pid_t pid = fork();
		if (pid)
			return;
		if (execvp("sqlitebrowser", args) == -1) {
#ifdef DEBUG
			std::cout << "[ERROR]: " << strerror(errno) << std::endl;
#endif
		}
	});
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
	waitpid(pid, &status, 0);

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