#include "ErrorWindow.h"

ErrorWindow::ErrorWindow(WINDOW *window): Window(window)
{
}

ErrorWindow::~ErrorWindow()
{
}

void	ErrorWindow::display()
{
	this->clear();
	this->reset_cursor();
	this->draw_border();

	this->refresh();
}
