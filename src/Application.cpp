
#include "src/Application.hpp"

Application::Application() :
  _mainWindow("emotion detector"),
  _mouthWindow("your mouth", 670, 0),
  _smileyWindow("your emotion", 670, 200),
  _imgHappy(cvLoadImage("data/happy.jpg")),
  _imgSad(cvLoadImage("data/sad.jpg")) {}

Application::~Application() {}

void Application::onStart() {}

void Application::onUpdate() {}

void Application::onEvent(int key) {}
