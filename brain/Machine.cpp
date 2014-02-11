
#include <highgui.h>
#include "Json.hpp"
#include "brain/Machine.hpp"

namespace brain {

Machine::Machine() :
  _imgSize(0),
  _nbImgs(0) {}

Machine::~Machine() {}

void Machine::train(std::string const &path) {
  Json data;

  data.load("data.json");

  // Get data from json.
  Json::Array const &happyImages = data["happy"];
  Json::Array const &sadImages = data["sad"];
  std::string const &firstImage = happyImages[0];
  CvSize sz = cvGetSize(cvLoadImage(firstImage.c_str()));
  _imgSize = sz.width * sz.height;
  _nbImgs = happyImages.size() + sadImages.size();

  // Initialize cv materials.
  cv::Mat sum = cv::Mat::zeros(_imgSize, 1, CV_32FC1);
  cv::Mat matrix(_imgSize, _nbImgs, CV_32FC1);
  std::size_t offset = 0;

  // Train from happy images.
  for (std::string const &path : happyImages) {
    std::cout << "Load [" << offset << "] " << path << std::endl;
    cv::Mat m = cvLoadImageM(path.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
    m = m.t();
    m = m.reshape(1, _imgSize);
    m.convertTo(m, CV_32FC1);
    m.copyTo(matrix.col(offset));
    sum = sum + m;
    ++offset;
  }

  // Train from sad images.
  for (std::string const &path : sadImages) {
    std::cout << "Load [" << offset << "] " << path << std::endl;
    cv::Mat m = cvLoadImageM(path.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
    m = m.t();
    m = m.reshape(1, _imgSize);
    m.convertTo(m, CV_32FC1);
    m.copyTo(matrix.col(offset));
    sum = sum + m;
    ++offset;
  }

  // Compute eigen vectors from the images sum.
  cv::Mat mean = sum / float(_nbImgs);
  cv::Mat crossMatrix = cv::Mat(_imgSize, _nbImgs, CV_32FC1);
  for (std::size_t i = 0; i < _nbImgs; ++i)
    crossMatrix.col(i) = matrix.col(i) - mean;
  cv::Mat cMatrix = crossMatrix.t() * crossMatrix;
  cv::Mat vMatrix, lMatrix;
  eigen(cMatrix, lMatrix, vMatrix);

  // Compute projection matrix.
  cv::Mat uMatrix = crossMatrix * vMatrix;
  _projectionMatrix = uMatrix.t();

  // project the training set to the faces space
  _trainSet = _projectionMatrix * crossMatrix;

}

bool Machine::isSmile(IplImage *mouth) const {
  if (_imgSize == 0 || _nbImgs == 0)
    throw std::runtime_error("cannot detect without training data");
  double min = 1000000000000000.0;
  int mini;
  cv::Mat mat = mouth;
  mat = mat.t();
  mat = mat.reshape(1, _imgSize);
  mat.convertTo(mat, CV_32FC1);
  cv::Mat cross = _projectionMatrix * mat;

  // find the minimum distance vector
  for (std::size_t i = 0; i < _nbImgs; i++) {
    double n = norm(cross - _trainSet.col(i));
    if (min > n) {
      min = n;
      mini = i;
    }
  }
  return mini != 1;
}

}
