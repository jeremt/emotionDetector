
#pragma once

#include "brain/Machine.hpp"
#include "brain/DataGenerator.hpp"
#include "cvwrapper/Capture.hpp"
#include "cvwrapper/FaceDetector.hpp"
#include "cvwrapper/Window.hpp"
#include "cvwrapper/Image.hpp"
#include "cvwrapper/Application.hpp"

class Application : public cvwrapper::Application {
public:
  Application();
  ~Application();

  void onStart(utils::Command const &command);
  void onUpdate();
  void onEvent(int key);

private:
  brain::Machine _machine;
  brain::DataGenerator _dataGenerator;
  cvwrapper::FaceDetector _detector;
  cvwrapper::Capture _cam;
  cvwrapper::Window _mainWindow;
  cvwrapper::Window _mouthWindow;
  IplImage *_mouth;
};

