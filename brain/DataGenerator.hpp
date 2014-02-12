
#pragma once

#include <cv.h>
#include "Json.hpp"

namespace brain {

// Generate and update a dataset image new images.
class DataGenerator {
public:

  // Default constructor.
  DataGenerator();

  // Empty destructor.
  ~DataGenerator();

  // Load the data generator from the given json file.
  void loadFromJson(std::string const &path);

  // Save the data generator to the given json file.
  void saveToJson(std::string const &path);

  // Add an image to the data set. The image should match with a specific
  // |pattern| type.
  void addImage(IplImage *image, std::string const &pattern);

private:
  Json _json;
};

}  // namespace brain
