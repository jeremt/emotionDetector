
#pragma once

#include <cv.h>
#include <string>

namespace brain {

// Simple machine learning which will detect the mouth of people according
// a mouth data set saved from the program.
class Machine {
public:

  // Default constructor.
  Machine();

  // Empty destructor.
  ~Machine();

  // Train the machine from a json which contains the path to all happy and
  // sad training images (e.g data.json).
  void train(std::string const &path);

  // Check if the given mouth is a smile or not.
  bool isSmile(IplImage *mouth) const;

private:
  cv::Mat _trainSet;
  cv::Mat _projectionMatrix;
  std::size_t _imgSize;
  std::size_t _nbImgs;

};

} // namespace brain
