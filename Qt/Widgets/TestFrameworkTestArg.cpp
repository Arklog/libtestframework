#include "Qt/Widgets/TestFrameworkTestArg.h"

TestFrameworkTestArg::TestFrameworkTestArg(t_socket_data d) : socket_data(d) {
	std::string str;

	this->layout = new QHBoxLayout();
	str = "";
	for (size_t i = 0; i < d.nargs; ++i)
		str += d.args[i];
	this->text = new QLabel(QString(str.c_str()));
	this->layout->addWidget(this->text);
	this->setLayout(this->layout);
}

TestFrameworkTestArg::~TestFrameworkTestArg() { delete this->layout; }

bool TestFrameworkTestArg::is_error() const { return !socket_data.result; }