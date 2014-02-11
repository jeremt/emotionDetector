
#pragma once

#include <cv.h>
#include <string>

namespace brain {

// Generate and update a dataset image new images.
class DataGenerator {
public:

  // Generate a dataset from the path of its json config file. If its doesnt
  // exist it will automaticaly create the file, and a data directory in the
  // same folder.
  DataGenerator(std::string const &path);

  // Empty destructor.
  ~DataGenerator();

  // Add an image to the data set. The image should match with a specific
  // |pattern| type.
  void addImage(IplImage *image, std::string const &pattern);
};

}  // namespace brain
