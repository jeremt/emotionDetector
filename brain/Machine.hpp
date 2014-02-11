
#pragma once

#include <cv.h>
#include <string>

namespace brain {

// Simple machine learning which will detect patterns from image data sets.
class Machine {
public:

  // Default constructor.
  Machine();

  // Empty destructor.
  ~Machine();

  // Load the data from a json data file.
  void loadFromJson(std::string const &path);

  // Add a image for a specific pattern from its |name|.
  void addImage(std::string const &name, std::string const &path);

  // Train the machine using the registered data.
  void train();

  // Return the detected pattern from the given image.
  std::string detect(IplImage *mouth) const;

private:
  std::map<std::string, std::vector<std::string>> _imgPatterns;
  cv::Mat _trainSet;
  cv::Mat _projectionMatrix;
  std::size_t _imgSize;
  std::size_t _nbImgs;

};

} // namespace brain
