#ifndef TESTWINDOW_H
# define TESTWINDOW_H

# include "Gui/Window.h"
# include "Test/TestManager.h"

class TestWindow: public Window
{
	public:
		TestWindow(WINDOW *window);
		virtual ~TestWindow();

		void	display() override;
};
#endif
