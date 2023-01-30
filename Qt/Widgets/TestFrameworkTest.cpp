#include "Qt/Widgets/TestFrameworkTest.h"
#include "testframework/testframework/TestFramework.h"

TestFrameworkTest::TestFrameworkTest(QWidget *parent, const TestBase *test) {
	this->testname = test->get_name();
	this->test_id = test->get_id();
	this->index_max = test->get_test_numbers() - 1;
	this->timer = new QTimer(this);
	this->label = new QLabel();
	this->label->setText(QObject::tr(this->testname.c_str()));
	this->progress = new QProgressBar();
	this->progress->setRange(0, test->get_test_numbers());
	this->progress->setValue(0);
	this->layout = new QGridLayout(this);
	this->layout->addWidget(this->label, 0, 0, 1, 1);
	this->layout->addWidget(this->progress, 0, 1, 1, 2);
}

TestFrameworkTest::~TestFrameworkTest() {
	delete this->timer;
	delete this->label;
	delete this->progress;
	delete this->layout;
}

std::string TestFrameworkTest::get_test_name() const { return this->testname; }

void TestFrameworkTest::start() {}

void TestFrameworkTest::stop() {}

void TestFrameworkTest::incr() {
	this->progress->setValue(this->progress->value() + 1);
}

void TestFrameworkTest::process_data(t_socket_data d) {
	this->incr();
	this->progress->update();
}

void TestFrameworkTest::update_info() {}