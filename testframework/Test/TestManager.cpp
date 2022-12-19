#include "Test/TestManager.h"
#include "TestManager.h"

std::shared_ptr<TestManager> TestManager::_current =
    std::shared_ptr<TestManager>(nullptr);

TestManager::TestManager()
    : _tests(std::vector<Test *>()), _iter(this->_tests.begin()) {}

TestManager::~TestManager() {
  std::vector<Test *>::iterator iter;

  for (iter = this->_tests.begin(); iter != this->_tests.end(); ++iter)
    delete *iter;
}

std::shared_ptr<TestManager> TestManager::get() {
  if (!TestManager::_current)
    TestManager::_current = std::shared_ptr<TestManager>(new TestManager());
  return TestManager::_current;
}

void TestManager::add_test(Test *t) {
  this->_tests.push_back(t);
  this->_iter = this->_tests.begin();
}

std::vector<Test *> TestManager::get_tests() { return (this->_tests); }

std::vector<Test *> TestManager::get_executed(bool all, bool success) {
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
  if (this->_iter != this->_tests.end()) {
    (*(this->_iter))->run();
    if ((*this->_iter)->executed())
      (this->_iter)++;
    return (true);
  }
  return (false);
}

bool TestManager::finished() const {
  for (auto i : this->_tests)
    if (!i->executed())
      return (false);
  return (true);
}
void TestManager::run_all() {
  using g = std::lock_guard<std::mutex>;
  auto l = [this]() {
    Test *t;
    g *guard;

    while (!this->finished()) {
      guard = new g(this->_iter_mutex);
      if (this->_iter == this->_tests.end()) {
        delete guard;
        return;
      } else
        t = *(this->_iter++);
      delete guard;
      while (!t->executed())
        t->run();
    }
  };

  for (int i = 0; i < MANAGER_THREADS; ++i)
    this->_th[i] = std::thread(l);
  for (int i = 0; i < MANAGER_THREADS; ++i)
    this->_th[i].join();
}