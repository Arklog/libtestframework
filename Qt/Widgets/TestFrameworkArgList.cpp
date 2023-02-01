#include "Qt/Widgets/TestFrameworkTestArgList.h"

TestFrameworkTestArgList::TestFrameworkTestArgList() {
	_display_all = true;
	this->scroll = new QScrollArea();
	this->central_widget = new QWidget();
	this->layout = new QVBoxLayout(central_widget);
	this->main_layout = new QVBoxLayout(this);

	this->scroll->setWidget(this->central_widget);
	this->scroll->setWidgetResizable(true);
	this->main_layout->addWidget(this->scroll);
	this->setLayout(this->main_layout);
}

TestFrameworkTestArgList::~TestFrameworkTestArgList() {
	delete this->main_layout;
}

void TestFrameworkTestArgList::add_data(t_socket_data d) {
	TestFrameworkTestArg *arg;
#ifdef DEBUG
	cout_mutex.lock();
	std::cout << "[INFO]: adding socket data to arg list\n";
	cout_mutex.unlock();
#endif
	arg = new TestFrameworkTestArg(d);
	this->layout->addWidget(arg);
	this->vec.push_back(arg);
	if (!_display_all && d.result)
		arg->hide();
	this->update();
}

void TestFrameworkTestArgList::display_all(bool display_all) {
	if (!display_all) {
		for (auto i : this->vec)
			if (!i->is_error())
				i->hide();
	} else {
		for (auto i : this->vec)
			i->show();
	}
	_display_all = display_all;
}