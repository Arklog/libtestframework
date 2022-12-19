#include "Gui/TestWindow.h"

TestWindow::TestWindow(WINDOW *window): Window(window, '#', 3, 2)
{
}

TestWindow::~TestWindow()
{
}

void	TestWindow::display()
{
	this->clear();
	this->reset_cursor();

	this->set_y(this->get_y() + 2);
	std::vector<Test *>	vec = TestManager::get()->get_tests();
	for (const Test *iter: vec)
	{
		auto vec = (*iter).to_string();

		for (auto str: vec)
		{
			this->set_x(3);
			wprintw(this->get(), "%s", str.c_str());
		}
		if (vec.size() > 1)
			this->set_y(this->get_y() + vec.size());
		else
			this->set_y(this->get_y() + 1);
	}

	this->draw_border();
	this->refresh();
}
