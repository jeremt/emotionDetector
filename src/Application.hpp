
#pragma once

#include "cvwrapper/Capture.hpp"
#include "cvwrapper/Detector.hpp"
#include "cvwrapper/Window.hpp"
#include "cvwrapper/Image.hpp"
#include "brain/Machine.hpp"
#include "cvwrapper/Application.hpp"

class Application : public cvwrapper::Application {
public:
  Application();
  ~Application();

  void onStart();
  void onUpdate();
  void onEvent(int key);

private:
  brain::Machine _machine;
  cvwrapper::Detector _detector;
  cvwrapper::Capture _cam;
  cvwrapper::Window _mainWindow;
  cvwrapper::Window _mouthWindow;
};

