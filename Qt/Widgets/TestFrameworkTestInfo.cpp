#include "Qt/Widgets/TestFrameworkTestInfo.h"
#include "testframework/Test/TestManager.h"

TestFrameworkTestInfo::TestFrameworkTestInfo() noexcept : current_test(-1) {
	QHBoxLayout *t;

	this->layout = new QVBoxLayout();
	this->buttons = new QGroupBox();

	t = new QHBoxLayout();
	button_show_all = new QRadioButton("all");
	button_show_error = new QRadioButton("error");
	connect(button_show_all, &QRadioButton::toggled, [this]() {
		for (auto i : this->vec) {
			i->display_all(true);
		}
	});
	connect(button_show_error, &QRadioButton::toggledc132, [this]() {
		for (auto i : this->vec) {
			i->display_all(false);
		}
	});
	t->addWidget(button_show_all);
	t->addWidget(button_show_error);

	this->buttons->setLayout(t);
	this->layout->addWidget(this->buttons);
	this->setLayout(this->layout);
}

TestFrameworkTestInfo::~TestFrameworkTestInfo() noexcept {
	delete this->layout;
}

void TestFrameworkTestInfo::set_test(size_t test_id) {
	TestFrameworkTestArgList *current;
#ifdef DEBUG
	cout_mutex.lock();
	std::cout << "[INFO]: setting test info\n";
	cout_mutex.unlock();
#endif

	if (this->current_test == -1) {
		this->layout->addWidget(vec.at(test_id));
		this->current_test = test_id;
#ifdef DEBUG
		cout_mutex.lock();
		std::cout << "[INFO]: test set for first time\n";
		cout_mutex.unlock();
#endif
		this->update();
		return;
	}

	current = this->vec.at(current_test);
	this->layout->replaceWidget(current, this->vec.at(test_id));
	this->current_test = test_id;
#ifdef DEBUG
	cout_mutex.lock();
	std::cout << "[INFO]: test set\n";
	cout_mutex.unlock();
#endif
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
#ifdef DEBUG
	cout_mutex.lock();
	std::cout << "[INFO]: test info widget: initiating\n";
	cout_mutex.unlock();
#endif
	this->vec.clear();
	for (auto i :
		 TestFramework::get_instance()->get_test_manager()->get_tests()) {
		(void)i;
		this->vec.push_back(new TestFrameworkTestArgList());
	}
}