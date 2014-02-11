
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

  // Train the machine from the given |csvPath|. The file is formated like the
  // following example:
  //
  //   happy:path/to/mouth_1.png
  //   happy:path/to/mouth_2.png
  //   sad:path/to/mouth_3.png
  //   sad:path/to/mouth_4.png
  //
  void train(std::string const &csvPath);

  // Check if the given mouth is a smile or not.
  bool isSmile(IplImage *mouth) const;

private:
  cv::Mat _trainSet;
  cv::Mat _projectionMatrix;

};

} // namespace brain
