#include "Qt/Widgets/TestFrameworkTest.h"
#include "Qt/Widgets/TestFrameworkTestArgList.h"
#include "Qt/Widgets/TestFrameworkTestInfo.h"
#include "testframework/testframework/TestFramework.h"

std::function<void(int)> TestFrameworkTest::on_click_callback =
	[](size_t test_id) { TestFrameworkTest::info_ptr->set_test(test_id); };

TestFrameworkTestInfo *TestFrameworkTest::info_ptr = nullptr;

TestFrameworkTest::TestFrameworkTest(QWidget *parent, const TestBase *test)
	: QWidget(parent) {
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

	connect(this, &TestFrameworkTest::mousePressEvent, this,
			&TestFrameworkTest::select);
}

TestFrameworkTest::~TestFrameworkTest() {
	delete this->timer;
	delete this->label;
	delete this->progress;
	delete this->layout;
}

std::string TestFrameworkTest::get_test_name() const { return this->testname; }

void TestFrameworkTest::incr() {
	this->progress->setValue(this->progress->value() + 1);
}

void TestFrameworkTest::select() {
#ifdef DEBUG
	cout_mutex.lock();
	std::cout << "[INFO]: test widget: clicked\n";
	cout_mutex.unlock();
#endif
	TestFrameworkTest::on_click_callback(this->test_id);
}

void TestFrameworkTest::process_data(t_socket_data d) {
	this->incr();
	this->progress->update();
}

void TestFrameworkTest::update_info() {}