
#pragma once

#include <cv.h>

namespace cvwrapper {

// Simple class used to detect shapes from pictures using OpenCV api.
class Detector {
public:

  // Load all files used from detection from |data_dir| which is the directory
  // which will contains all data files (e.g. haarcascade_XXXX.xml).
  Detector(std::string const &data_dir = "data");

  // Release the loaded files.
  ~Detector();

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
