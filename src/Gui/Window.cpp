#include "Gui/Window.h"

Window::Window(WINDOW *window): _window(window), _border('#')
{
}

Window::~Window()
{
	delwin(this->_window);
}

void	Window::reset_cursor()
{
	if (!this->get())
		return ;
	this->get()->_curx = 0;
	this->get()->_cury = 0;
}

void	Window::clear()
{
	if (!this->get())
		return ;
	wclear(this->get());
}

WINDOW*	Window::get()
{
	return this->_window;
}

void	Window::draw_border()
{
	char	c;

	c = this->get_border();
	wborder(this->get(), c, c, c, c, c, c, c, c);
}

void	Window::set_border(char c)
{
	if (isprint(c))
		this->_border = c;
}

char	Window::get_border()
{
	return (this->_border);
}

void	Window::refresh()
{
	if (this->get())
		wrefresh(this->get());
}

int		Window::get_x()
{
	if (this->get())
		return (this->get()->_curx);
	else
		return (0);
}

void	Window::set_x(int x)
{
	if (!this->get())
		return ;
	if (x <= this->get_maxx())
		this->get()->_curx = (short)x;
}

int		Window::get_y()
{
	if (this->get())
		return (this->get()->_cury);
	else
		return (0);
}

void	Window::set_y(int y)
{
	if (!this->get())
		return ;
	if (y <= this->get_maxy())
		this->get()->_cury = (short)y;
}

int		Window::get_maxx()
{
	if (this->get())
		return (getmaxx(this->get()));
	else
		return (0);
}

int		Window::get_maxy()
{
	if (this->get())
		return (getmaxy(this->get()));
	else
		return (0);
}
