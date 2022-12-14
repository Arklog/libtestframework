#ifndef MAINWINDOW_H
# define MAINWINDOW_H

# include "Gui/TestWindow.h"
# include "Gui/ErrorWindow.h"

class MainWindow: public Window
{
	private:
		ErrorWindow	*_err;
		TestWindow	*_tests;

	public:
		MainWindow();
		virtual ~MainWindow();

		void	display() override;
		void	display_loop();
};

#endif
