#include <QtWidgets/QApplication>
#include "Qt/Window/MainWindow.h"
#include "Qt/main.h"

int testframework_start_gui(int argc, char **argv)
{
	QApplication app(argc, argv);
	MainWindow window;
	
	return app.exec();
}