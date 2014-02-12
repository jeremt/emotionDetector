
#include "cvwrapper/Image.hpp"
#include "brain/PatternFinder.hpp"

namespace brain {

PatternFinder::PatternFinder() {}

PatternFinder::~PatternFinder() {}

void PatternFinder::loadFromJson(std::string const &path) {
  _machine.loadFromJson(path);
  _machine.train();
  _detector.load("data/haarcascade_frontalface_default.xml");
}

std::string PatternFinder::find(IplImage *image) const {
  CvRect *face = _detector.detectBestFace(image);
  if (face == NULL)
    throw std::runtime_error("cannot find any face");
  std::cout << "Face found" << std::endl;
  IplImage *mouth = cvwrapper::equalizeImage(
      cvwrapper::ajustImage(image, face, 0.7, 0.6));
  return _machine.detect(mouth);
}

}
