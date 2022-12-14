#ifndef ERRORWINDOW_H
# define ERRORWINDOW_H

# include "Window.h"

class ErrorWindow: public Window
{
	private:
	public:
		ErrorWindow(WINDOW *window);
		virtual ~ErrorWindow();

		void	display() override;
};

#endif
