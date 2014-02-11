
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
  std::size_t imgSize = sz.width * sz.height;
  std::size_t nbImgs = data.size();

  cv::Mat sum = cv::Mat::zeros(imgSize, 1, CV_32FC1);;
  cv::Mat matrix(imgSize, nbImgs, CV_32FC1);

  // Parse all images.
  // for (std::size_t i = 0; i < nbImgs; ++i) {
  //   cv::Mat m = cvLoadImageM(row.second.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
  //   m = m.t();
  //   m = m.reshape(1, imgSize);
  //   m.convertTo(m, CV_32FC1);
  //   m.copyTo(matrix.col(i));
  //   sum = sum + m;
  // }
}

bool Machine::isSmile(IplImage *mouth) const {
  return false;
}

}
