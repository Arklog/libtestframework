#include "Gui/MainWindow.h"

MainWindow::MainWindow(): Window(initscr()), _err(NULL), _tests(NULL)
{
	int	maxx;
	int	maxy;

	if (!this->get())
		exit(1);
	maxx = getmaxx(this->get());
	maxy = getmaxy(this->get());
	this->_err = new ErrorWindow(subwin(this->get(), 
			maxy,
			maxx / 2,
			0,
			maxx - maxx / 2
	));
	this->_tests = new TestWindow(subwin(this->get(),
			maxy,
			maxx - maxx / 2,
			0,
			0
	));
}

MainWindow::~MainWindow()
{
	delete this->_err;
	delete this->_tests;
}

void	MainWindow::display()
{
	this->clear();
	this->reset_cursor();

	this->_err->display();
	this->_tests->display();

	refresh();
}

void	MainWindow::display_loop()
{
	auto l = [](){
		TestManager::get()->run_all();
	};

	this->display();
	std::thread th(l);
	while (!TestManager::get()->finished())
	{
		this->display();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	th.join();
	this->display();
	getch();
}
