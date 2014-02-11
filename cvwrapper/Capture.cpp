
#include <stdexcept>
#include "cvwrapper/Capture.hpp"

namespace cvwrapper {

Capture::Capture() {
  _capture = cvCaptureFromCAM(0);
  if (_capture == NULL)
    throw std::runtime_error("cannot create capture");
}

Capture::~Capture() {
  cvReleaseCapture(&_capture);
}

IplImage *Capture::queryFrame() const {
  return cvQueryFrame(_capture);
}

}  // namespace cvwrapper
