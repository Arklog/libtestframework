#include "Qt/Widgets/TestFrameworkTestInfo.h"

TestFrameworkTestInfo::TestFrameworkTestInfo(size_t testnumber)
{
	this->clear();
	for (size_t i = 0; i < testnumber; ++i)
		socket_datas.push_back(std::vector<t_socket_data>{});
}

TestFrameworkTestInfo::~TestFrameworkTestInfo() {
}

void TestFrameworkTestInfo::clear()
{
	QRadioButton *tmp;
	QHBoxLayout *buttons_layout;

	if (this->layout)
		delete this->layout;
	this->socket_datas.clear();

	this->layout = new QVBoxLayout();
	this->buttons = new QGroupBox();

	buttons_layout = new QHBoxLayout();
	buttons_layout->addWidget(new QRadioButton("all"));
	buttons_layout->addWidget(new QRadioButton("errors"));

	this->buttons->setLayout(buttons_layout);
	this->layout->addWidget(this->buttons);
}
