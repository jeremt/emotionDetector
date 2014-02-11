
#include <highgui.h>
#include "brain/DataGenerator.hpp"

namespace brain {

DataGenerator::DataGenerator(std::string const &path) {
  (void)path;
}

DataGenerator::~DataGenerator() {}

void DataGenerator::addImage(IplImage *image, std::string const &pattern) {
  std::string path = pattern; // generate this path from the existing ones.
  cvSaveImage(path.c_str(), image);
}

}
