
#include "cvwrapper/FaceDetector.hpp"

namespace cvwrapper {

FaceDetector::FaceDetector() :
  _frontalfaceStorage(cvCreateMemStorage(0)),
  _frontalfaceCascade(NULL) {}

FaceDetector::~FaceDetector() {
  cvReleaseMemStorage(&_frontalfaceStorage);
  if (_frontalfaceCascade != NULL)
    cvReleaseHaarClassifierCascade(&_frontalfaceCascade);
}

void FaceDetector::load(std::string const &path) {
  _frontalfaceCascade = static_cast<CvHaarClassifierCascade *>(
      cvLoad(path.c_str()));
}

CvSeq *FaceDetector::detectFaces(IplImage *image) const {
  return cvHaarDetectObjects(image, _frontalfaceCascade, _frontalfaceStorage,
      1.3, 4, CV_HAAR_DO_CANNY_PRUNING, cvSize(50, 50));
}

CvRect *FaceDetector::detectBestFace(IplImage *image) const {
  CvSeq *faces = detectFaces(image);
  if (faces->total == 0)
    return NULL;
  CvRect *face = NULL;
  for (int i = 0; i < faces->total; ++i) {
    CvRect *r = reinterpret_cast<CvRect *>(cvGetSeqElem(faces, i));
    if (face == NULL || (face->width * face->height < r->width * r->height))
      face = r;
  }
  return face;
}

}  // namespace cvwrapper
