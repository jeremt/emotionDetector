
#include "cvwrapper/Detector.hpp"

namespace cvwrapper {

Detector::Detector(std::string const &data_dir) {
  _frontalfaceStorage = cvCreateMemStorage(0);
  _frontalfaceCascade = static_cast<CvHaarClassifierCascade *>(
      cvLoad((data_dir + "/haarcascade_frontalface_default.xml").c_str()));
}

Detector::~Detector() {
  cvReleaseMemStorage(&_frontalfaceStorage);
  cvReleaseHaarClassifierCascade(&_frontalfaceCascade);
}

CvSeq *Detector::detectFaces(IplImage *image) const {
  return cvHaarDetectObjects(image, _frontalfaceCascade, _frontalfaceStorage,
      1.3, 4, CV_HAAR_DO_CANNY_PRUNING, cvSize(50, 50));
}

CvRect *Detector::detectBestFace(IplImage *image) const {
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
