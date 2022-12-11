#ifndef TESTWINDOW_H
# define TESTWINDOW_H

# include "Window.h"
# include "TestManager.h"

class TestWindow: public Window
{
	public:
		TestWindow(WINDOW *window);
		virtual ~TestWindow();

		void	display() override;
};
#endif
