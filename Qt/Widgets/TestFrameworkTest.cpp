#include "Qt/Widgets/TestFrameworkTest.h"
#include "testframework/testframework/TestFramework.h"
#include "testframework/Database/Database.h"

TestFrameworkTest::TestFrameworkTest(QWidget *parent, const TestBase *test)
{
	this->testname = test->get_name();
	this->index_max = test->get_test_numbers() - 1;
	this->timer = new QTimer(this);
	this->label = new QLabel();
	this->label->setText(QObject::tr(this->testname.c_str()));
	this->progress = new QProgressBar();
	this->progress->setRange(0, test->get_test_numbers());
	this->layout = new QGridLayout(this);
	this->layout->addWidget(this->label, 0, 0, 1, 1);
	this->layout->addWidget(this->progress, 0, 1, 1, 2);
}

TestFrameworkTest::~TestFrameworkTest()
{
	delete this->timer;
	delete this->label;
	delete this->progress;
	delete this->layout;
}

std::string TestFrameworkTest::get_test_name() const
{
	return this->testname;
}

void TestFrameworkTest::start()
{
	connect(this->timer, &QTimer::timeout, this, &TestFrameworkTest::update_info);
	this->timer->setSingleShot(false);
	this->timer->start(100);
}

void TestFrameworkTest::stop()
{
	this->finished = true;
	this->timer->stop();
}

void TestFrameworkTest::update_info()
{
	t_test t;

	t = TestFramework::get_instance()->get_database()->get_test_info(this->testname);
	this->progress->setValue(t.results.size());
	this->progress->update();
}