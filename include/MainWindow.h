#ifndef MAINWINDOW_H
# define MAINWINDOW_H

# include "TestWindow.h"
# include "ErrorWindow.h"

class MainWindow: public Window
{
	private:
		ErrorWindow	*_err;
		TestWindow	*_tests;

	public:
		MainWindow();
		virtual ~MainWindow();

		void	display() override;
};

#endif
