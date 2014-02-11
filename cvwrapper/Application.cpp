
#include <highgui.h>
#include "cvwrapper/Application.hpp"

namespace cvwrapper {

Application::Application() :
  _isOpen(false),
  _keyWait(50) {}

Application::~Application() {}

void Application::run() {
  onStart();
  while (_isOpen) {
    onEvent(cvWaitKey(_keyWait));
    onUpdate();
  }
}

void Application::close() {
  _isOpen = false;
}

void Application::setKeyWait(float keyWait) {
  _keyWait = keyWait;
}

}
