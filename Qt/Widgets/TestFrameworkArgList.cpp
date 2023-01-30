#include "Qt/Widgets/TestFrameworkTestArgList.h"

TestFrameworkTestArgList::TestFrameworkTestArgList() {
	this->layout = new QVBoxLayout();
	this->setLayout(this->layout);
}

TestFrameworkTestArgList::~TestFrameworkTestArgList()

	noexcept {
	delete this->layout;
}

void TestFrameworkTestArgList::add_data(t_socket_data d) {
	this->layout->addWidget(new TestFrameworkTestArg(d));
	this->update();
}