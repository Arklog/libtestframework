#include "Gui/Window.h"
#include "Window.h"

Window::Window(WINDOW *window)
    : _window(window), _border('#'), _padx(0), _pady(0) {}

Window::Window(WINDOW *window, char border, int padx, int pady)
    : _window(window), _border(border), _padx(padx), _pady(pady) {}

Window::~Window() { delwin(this->_window); }

void Window::reset_cursor() {
  if (!this->get())
    return;
  this->set_x(0);
  this->set_y(0);
}

void Window::clear() {
  if (!this->get())
    return;
  wclear(this->get());
}

WINDOW *Window::get() { return this->_window; }

void Window::draw_border() {
  char c;

  c = this->get_border();
  wborder(this->get(), c, c, c, c, c, c, c, c);
}

void Window::set_border(char c) {
  if (isprint(c))
    this->_border = c;
}

char Window::get_border() { return (this->_border); }

void Window::refresh() {
  if (this->get())
    wrefresh(this->get());
}

int Window::get_x() {
  if (this->get())
    return (this->get()->_curx - this->get_padx());
  else
    return (0);
}

void Window::set_x(int x) {
  if (!this->get())
    return;
  if (x <= this->get_maxx())
    this->get()->_curx = (short)x + (short)this->get_padx();
}

int Window::get_y() {
  if (this->get())
    return (this->get()->_cury - this->_pady);
  else
    return (0);
}

void Window::set_y(int y) {
  if (!this->get())
    return;
  if (y <= this->get_maxy())
    this->get()->_cury = (short)y + (short)this->get_pady();
}

int Window::get_maxx() {
  if (this->get())
    return (getmaxx(this->get()));
  else
    return (0);
}

int Window::get_maxy() {
  if (this->get())
    return (getmaxy(this->get()));
  else
	return (0);
}

void Window::print(const char *str, bool nl)
{
	this->set_x(this->get_padx());
	wprintw(this->get(), "%s", str);
	this->set_y(this->get_y() + (int)nl);
}

int Window::get_padx() const
{
	return (this->_padx);
}

int Window::get_pady() const
{
	return (this->_pady);
}
