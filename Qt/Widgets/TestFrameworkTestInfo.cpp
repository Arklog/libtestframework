#include "Qt/Widgets/TestFrameworkTestInfo.h"
#include "testframework/Test/TestManager.h"

TestFrameworkTestInfo::TestFrameworkTestInfo() noexcept {
	QHBoxLayout *t;

	this->layout = new QVBoxLayout();
	this->buttons = new QGroupBox();

	t = new QHBoxLayout();
	t->addWidget(new QRadioButton("all"));
	t->addWidget(new QRadioButton("error"));

	this->buttons->setLayout(t);
	this->layout->addWidget(this->buttons);
	this->setLayout(this->layout);
}

TestFrameworkTestInfo::~TestFrameworkTestInfo() noexcept {
	delete this->layout;
}

void TestFrameworkTestInfo::set_test(size_t test_id) {
	TestFrameworkTestArgList *current;

	if (this->current_test == -1) {
		this->layout->addWidget(vec.at(test_id));
		return;
	}

	current = this->vec.at(current_test);
	this->layout->replaceWidget(current, this->vec.at(test_id));
	this->current_test = test_id;
	this->update();
}

void TestFrameworkTestInfo::add_test_data(t_socket_data d) {
	try {
		this->vec.at(d.id)->add_data(d);
	} catch (std::exception *e) {
#ifdef DEBUG
		cout_mutex.lock();
		std::cout << "[ERROR]: TestFrameworkTestInfo: " << e->what()
				  << std::endl;
		cout_mutex.unlock();
#endif
	}
}

void TestFrameworkTestInfo::init() {
	for (auto i :
		 TestFramework::get_instance()->get_test_manager()->get_tests())
		this->vec.push_back(new TestFrameworkTestArgList());
}