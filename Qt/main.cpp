#include <QtWidgets/QApplication>
#include "Qt/Window/MainWindow.h"
#include "testframework/testframework/TestFramework.h"

int main(int argc, char **argv)
{
	int code;
	QApplication app(argc, argv);
	MainWindow window;
	
	code = app.exec();
	return code;
}