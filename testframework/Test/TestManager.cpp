#include "Test/TestManager.h"
#include "TestManager.h"

std::shared_ptr<TestManager> TestManager::_current =
    std::shared_ptr<TestManager>(nullptr);

TestManager::TestManager()
    : _tests(std::vector<Test *>()), _iter(this->_tests.begin()) {}

TestManager::~TestManager() {
  std::vector<Test *>::iterator iter;

  std::lock_guard<std::mutex> gtests(this->_tests_mutex);
  for (iter = this->_tests.begin(); iter != this->_tests.end(); ++iter)
    delete *iter;
}

std::shared_ptr<TestManager> TestManager::get() {
  if (!TestManager::_current)
    TestManager::_current = std::shared_ptr<TestManager>(new TestManager());
  return TestManager::_current;
}

void TestManager::add_test(Test *t) {
  std::lock_guard<std::mutex> gtests(this->_tests_mutex);
  this->_tests.push_back(t);
  this->_iter = this->_tests.begin();
}

std::vector<Test *> TestManager::get_tests() {
  std::lock_guard<std::mutex> gtests(this->_tests_mutex);
  return (this->_tests);
}

std::vector<Test *> TestManager::get_executed(bool all, bool success) {
  std::lock_guard<std::mutex> gtests(this->_tests_mutex);
  std::vector<Test *> vec;
  std::vector<Test *>::iterator iter;

  for (iter = this->_tests.begin(); iter != this->_tests.end(); ++iter) {
    if ((*iter)->executed() && all)
      vec.push_back(*iter);
    else if ((*iter)->executed() && !all && (*iter)->result() == success)
      vec.push_back(*iter);
  }
  return (vec);
}

bool TestManager::run_one() {
  std::lock_guard<std::mutex> gtests(this->_tests_mutex);
  if (this->_iter != this->_tests.end()) {
    (*(this->_iter))->run();
    if ((*this->_iter)->executed())
      (this->_iter)++;
    return (true);
  }
  return (false);
}

bool TestManager::finished() {
  std::lock_guard<std::mutex> gtests(this->_tests_mutex);
  for (auto i : this->_tests)
    if (!i->executed())
      return (false);
  return (true);
}
void TestManager::run_all() {
  auto l = [this]() {
    Test *t;

    while (!this->finished()) {
      if (this->_iter == this->_tests.end()) {
        return;
      } else
        t = *(this->_iter++);
      while (!t->executed())
        t->run();
    }
  };

  for (int i = 0; i < MANAGER_THREADS; ++i)
    this->_th[i] = std::thread(l);
  for (int i = 0; i < MANAGER_THREADS; ++i)
    this->_th[i].join();
}