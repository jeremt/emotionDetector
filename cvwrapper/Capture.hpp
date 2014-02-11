
#pragma once

#include <cv.h>
#include <highgui.h>

namespace cvwrapper {

// Capture pictures from webcam using OpenCV api.
class Capture {
public:

  // Create the capture.
  Capture();

  // Release the capture.
  ~Capture();

  // Get the current frame of the webcam.
  IplImage *queryFrame() const;
private:
  CvCapture *_capture;
};

}
