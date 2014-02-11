
#include <highgui.h>
#include "Json.hpp"
#include "utils/Log.hpp"
#include "brain/Machine.hpp"

namespace brain {

Machine::Machine() :
  _imgSize(0),
  _nbImgs(0) {}

Machine::~Machine() {}

void Machine::loadFromJson(std::string const &path) {
  Json file;

  file.load(path);
  Json::Object const &data = file;
  for (auto p : data) {
    Json::Array const &imgPaths = p.second;
    for (std::string const &path : imgPaths)
      addImage(p.first, path);
  }
}

void Machine::addImage(std::string const &name, std::string const &path) {
  _imgPatterns[name].push_back(path);
}

void Machine::train() {

  // Get data from json.
  CvSize sz = cvGetSize(cvLoadImage(_imgPatterns.begin()->second[0].c_str()));
  _imgSize = sz.width * sz.height;
  _nbImgs = 0;
  for (auto const &pattern : _imgPatterns)
    _nbImgs += pattern.second.size();

  // Initialize cv materials.
  cv::Mat sum = cv::Mat::zeros(_imgSize, 1, CV_32FC1);
  cv::Mat matrix(_imgSize, _nbImgs, CV_32FC1);
  std::size_t offset = 0;

  // Compute sum and matrix from images data.
  for (auto const &pattern : _imgPatterns) {
    for (std::string const &path : pattern.second) {
      LOG_INFO << "[" << offset << "] [" << pattern.first << "] "
                << path << LOG_ENDL;
      cv::Mat m = cvLoadImageM(path.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
      m = m.t();
      m = m.reshape(1, _imgSize);
      m.convertTo(m, CV_32FC1);
      m.copyTo(matrix.col(offset));
      sum = sum + m;
      ++offset;
    }
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

std::string Machine::detect(IplImage *mouth) const {
  if (_imgSize == 0 || _nbImgs == 0)
    throw std::runtime_error("cannot detect without training data");
  float min = std::numeric_limits<float>::max();
  std::size_t minIndex = 0;

  // Apply preprocessor to mouth
  cv::Mat mat = mouth;
  mat = mat.t();
  mat = mat.reshape(1, _imgSize);
  mat.convertTo(mat, CV_32FC1);
  cv::Mat cross = _projectionMatrix * mat;

  // Find the index of the minimal value in the trainSet matrix
  for (std::size_t i = 0; i < _nbImgs; i++) {
    float n = norm(cross - _trainSet.col(i));
    if (min > n) {
      min = n;
      minIndex = i;
    }
  }

  LOG_DEBUG << "detected index " << minIndex << LOG_ENDL;

  // Get the pattern name from the index found
  // TODO(jeremie) modulo le nombre d'image dans le data set
  std::size_t i = 0;
  for (auto const &pattern : _imgPatterns) {
    if (i == minIndex / (_nbImgs >> 1))
      return pattern.first;
    ++i;
  }
  return "unknown";
}

}
