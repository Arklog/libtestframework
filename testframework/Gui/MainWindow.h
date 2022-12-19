#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef DEBUG
#include <iostream>
#endif

#include "Gui/ErrorWindow.h"
#include "Gui/TestWindow.h"
#include <chrono>
#include <thread>

class MainWindow : public Window {
private:
  ErrorWindow *_err;
  TestWindow *_tests;

public:
  MainWindow();
  virtual ~MainWindow();

  void display() override;
  void display_loop();
};

#endif
