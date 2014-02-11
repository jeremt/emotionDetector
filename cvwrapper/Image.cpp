
#include "cvwrapper/Image.hpp"

namespace cvwrapper {

IplImage *ajustImage(IplImage *image, CvRect *roi,
                     float widthCoef, float heightCoef) {
  int suby = roi->height * heightCoef;
  roi->height -= suby;
  roi->y += suby;
  int subx = (roi->width - roi->height) / 2 * widthCoef;
  roi->width -= subx * 2;
  roi->x += subx;
  cvSetImageROI(image, *roi);
  IplImage *result = cvCreateImage(cvSize(100, 100 * widthCoef), 8, 3);
  cvResize(image, result);
  cvResetImageROI(image);
  return result;
}

IplImage *equalizeImage(IplImage *image) {
  IplImage *result = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
  cvCvtColor(image, result, CV_RGB2GRAY);
  cvEqualizeHist(result, result);
  return result;
}

}
