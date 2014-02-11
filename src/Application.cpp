
#include "utils/Log.hpp"
#include "src/Application.hpp"

Application::Application() :
  _mainWindow("emotion detector"),
  _mouthWindow("input data", 0, 650) {}

Application::~Application() {}

void Application::onStart() {
  try {
    _machine.loadFromJson("data.json");
    _machine.train();
  } catch (std::exception const &e) {
    LOG_ERR << "an error occured: " << e.what() << LOG_ENDL;
  }
}

void Application::onUpdate() {

  try {

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
    IplImage *mouth = cvwrapper::equalizeImage(
        cvwrapper::ajustImage(img, face, 0.7, 0.6));
    _mainWindow.drawImage(img, mouth, 0, 0);

    // Detect the pattern
    _mainWindow.drawText(img, "Detected pattern: " + _machine.detect(mouth),
        cvPoint(20, 450), CV_RGB(255, 255, 255));

    // Update windows display
    _mouthWindow.display(mouth);
    _mainWindow.display(img);

  } catch (std::exception const &e) {
    LOG_ERR << "an error occured: " << e.what() << LOG_ENDL;
  }

}

void Application::onEvent(int key) {
  if (key == ESCAPE)
    close();
}
