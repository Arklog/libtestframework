#include "Qt/Widgets/TestFrameworkTest.h"

TestFrameworkTest::TestFrameworkTest(QWidget *parent, const TestBase *test)
{
	this->testname = test->get_name();
	this->label = new QLabel();
	this->label->setText(QObject::tr(this->testname.c_str()));
	this->progress = new QProgressBar();
	this->progress->setRange(0, test->get_test_numbers() - 1);
	this->layout = new QGridLayout(this);
	this->layout->addWidget(this->label, 0, 0, 1, 1);
	this->layout->addWidget(this->progress, 0, 1, 1, 2);
}

TestFrameworkTest::~TestFrameworkTest()
{
	delete this->label;
	delete this->progress;
	delete this->layout;
}