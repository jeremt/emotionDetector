
#pragma once

#include "cvwrapper/Capture.hpp"
#include "cvwrapper/Detector.hpp"
#include "cvwrapper/Window.hpp"
#include "cvwrapper/Image.hpp"
#include "brain/HappynessMachine.hpp"
#include "cvwrapper/Application.hpp"

class Application : public cvwrapper::Application {
public:
  Application();
  ~Application();

  void onStart();
  void onUpdate();
  void onEvent(int key);

private:
  brain::HappynessMachine _machine;
  cvwrapper::Detector _detector;
  cvwrapper::Capture _cam;
  cvwrapper::Window _mainWindow;
  cvwrapper::Window _mouthWindow;
  cvwrapper::Window _smileyWindow;
  IplImage *_imgHappy;
  IplImage *_imgSad;
};

