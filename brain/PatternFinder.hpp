
#pragma once

#include "cvwrapper/FaceDetector.hpp"
#include "brain/Machine.hpp"

namespace brain {

// Find emotion pattern using a machine learning algorithm.
class PatternFinder {
public:
  PatternFinder();
  ~PatternFinder();
  void loadFromJson(std::string const &path);
  std::string find(IplImage *image) const;

private:
  brain::Machine _machine;
  cvwrapper::FaceDetector _detector;
};

}
