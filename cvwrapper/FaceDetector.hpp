
#pragma once

#include <cv.h>

namespace cvwrapper {

// Simple class used to detect faces from pictures using OpenCV api.
class FaceDetector {
public:

  // Initialize the detector.
  FaceDetector();

  // Release the loaded files.
  ~FaceDetector();

  // Load the xml used to detect faces.
  void load(std::string const &path = "haarcascade_frontalface_default.xml");

  // Detect human faces from the given |image|.
  CvSeq *detectFaces(IplImage *image) const;

  // Detect the best face on the screen, if no face detected it will return
  // a null pointer.
  CvRect *detectBestFace(IplImage *image) const;

private:
  CvMemStorage *_frontalfaceStorage;
  CvHaarClassifierCascade *_frontalfaceCascade;

};

}  // namespace cvwrapper
