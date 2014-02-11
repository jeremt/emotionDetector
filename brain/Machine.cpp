
#include <highgui.h>
#include "utils/loadCsv.hpp"
#include "brain/Machine.hpp"

namespace brain {

Machine::Machine() {}

Machine::~Machine() {}

void Machine::train(std::string const &csvPath) {
  utils::CsvData const &data = utils::loadCsv(csvPath);

  // Compute image size.
  CvSize sz = cvGetSize(cvLoadImage(data[0].second.c_str()));
  std::size_t size = sz.width * sz.height;

  cv::Mat sum = cv::Mat::zeros(size, 1, CV_32FC1);;
  cv::Mat matrix(size, data.size(), CV_32FC1);

  // Parse all images.
  for (utils::CsvRow const &row : data) {

  }
}

bool Machine::isSmile(IplImage *mouth) const {
  return false;
}

}
