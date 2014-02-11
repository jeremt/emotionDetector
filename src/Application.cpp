
#include "utils/Log.hpp"
#include "src/Application.hpp"

Application::Application() :
  _mainWindow("emotion detector"),
  _mouthWindow("your mouth", 670, 0),
  _smileyWindow("your emotion", 670, 200),
  _imgHappy(cvLoadImage("data/happy.jpg")),
  _imgSad(cvLoadImage("data/sad.jpg")) {}

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

    // find the mouth
    CvRect *face = _detector.detectBestFace(img);
    if (face == NULL) {
      LOG_WARN << "no face detected" << LOG_ENDL;
      _mainWindow.display(img);
      return;
    }
    _mainWindow.drawRect(img, face, CV_RGB(200,50,50));

    // Get the mouse and set it in black and white
    IplImage *mouth = cvwrapper::equalizeImage(
        cvwrapper::ajustImage(img, face, 0.7, 0.6));

    // Update windows display
    std::string const &result = _machine.detect(mouth);
    LOG_DEBUG << "result = " << result << LOG_ENDL;
    _smileyWindow.display(result == "happy" ? _imgHappy : _imgSad);
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
