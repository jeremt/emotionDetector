
#include "src/Application.hpp"

Application::Application() :
  _mainWindow("emotion detector"),
  _mouthWindow("your mouth", 670, 0),
  _smileyWindow("your emotion", 670, 200),
  _imgHappy(cvLoadImage("data/happy.jpg")),
  _imgSad(cvLoadImage("data/sad.jpg")) {}

Application::~Application() {}

void Application::onStart() {
  _machine.train("data.json");
}

void Application::onUpdate() {

  // Get one frame
  IplImage *img = _cam.queryFrame();

  // find the mouth
  CvRect *face = _detector.detectBestFace(img);
  if (face == NULL) {
    std::cout << "No face detected..." << std::endl;
    _mainWindow.display(img);
    return;
  }
  _mainWindow.drawRect(img, face, CV_RGB(200,50,50));

  // Get the mouse and set it in black and white
  IplImage *mouth = cvwrapper::equalizeImage(
      cvwrapper::ajustImage(img, face, 0.7, 0.6));

  // Update windows display
  _smileyWindow.display(_machine.isSmile(mouth) ? _imgHappy : _imgSad);
  _mouthWindow.display(mouth);
  _mainWindow.display(img);

}

void Application::onEvent(int key) {
  if (key == ESCAPE)
    close();
}
