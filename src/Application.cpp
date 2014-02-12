
#include "utils/Log.hpp"
#include "src/Application.hpp"

Application::Application() :
  _mainWindow("emotion detector"),
  _mouthWindow("input data", 0, 650),
  _mouth(NULL) {}

Application::~Application() {}

void Application::onStart(utils::Command const &command) {
  setKeyWait(300);
  _machine.loadFromJson(command.getOpt<std::string>("path"));
  _machine.train();
  _detector.load("data/haarcascade_frontalface_default.xml");
}

void Application::onUpdate() {

  // Get one frame
  IplImage *img = _cam.queryFrame();

  // Find the head
  CvRect *face = _detector.detectBestFace(img);
  if (face == NULL) {
    _mainWindow.drawText(img, "No face detected!",
      cvPoint(20, 450), CV_RGB(255, 255, 255));
    _mainWindow.display(img);
    return;
  }
  _mainWindow.drawRect(img, face, CV_RGB(255, 255, 255));

  // Find the mouse and detect the pattern
  _mouth = cvwrapper::equalizeImage(
      cvwrapper::ajustImage(img, face, 0.7, 0.6));
  // _mainWindow.drawImage(img, mouth, 0, 0);

  // Detect the pattern
  _mainWindow.drawText(img, "Detected pattern: " + _machine.detect(_mouth),
      cvPoint(20, 450), CV_RGB(255, 255, 255));

  // Update windows display
  std::string help("[ESC] Quit - [H] Happy screenshot - [S] Sad screeshot");
  _mainWindow.drawText(img, help, cvPoint(20, 50), CV_RGB(255, 255, 255));
  _mouthWindow.display(_mouth);
  _mainWindow.display(img);

}

void Application::onEvent(int key) {
  if (key == ESCAPE)
    close();
  else if (_mouth && (key == 'h' || key == 's')) {
    _dataGenerator.addImage(_mouth, key == 'h' ? "happy" : "sad");
    _mouth = NULL;
  }
}
