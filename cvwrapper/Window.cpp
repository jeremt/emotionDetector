
#include "cvwrapper/Window.hpp"

namespace cvwrapper {

Window::Window(std::string const &name) :
  _name(name) {
  cvNamedWindow(_name.c_str(), CV_WINDOW_AUTOSIZE);
  cvInitFont(&_font, CV_FONT_HERSHEY_SIMPLEX, 1.0, 0.5, 0, 1);
}

Window::Window(std::string const &name, std::size_t x, std::size_t y) :
  Window(name) {
    move(x, y);
}

Window::~Window() {
  cvDestroyWindow(_name.c_str());
}

void Window::display(IplImage *image) const {
  cvShowImage(_name.c_str(), image);
}

void Window::drawRect(IplImage *image, CvRect *r, CvScalar const &color) const {
  CvPoint const &p1 = cvPoint(r->x, r->y);
  CvPoint const &p2 = cvPoint(r->x + r->width, r->y + r->height);
  cvRectangle(image, p1, p2, color, 3);
}

void Window::drawText(IplImage *image,
                      std::string const &text,
                      CvPoint const &pt,
                      CvScalar const &color) const {
  cvPutText(image, text.c_str(), pt, &_font, color);
}

void Window::drawImage(IplImage *image,
                       IplImage *smallImage,
                       std::size_t x,
                       std::size_t y) {
  CvSize const &pt = cvGetSize(smallImage);
  cvSetImageROI(image, cvRect(x, y, pt.width, pt.height));
  // IplImage *img2 = cvCreateImage(cvGetSize(image),
  //                                image->depth,
  //                                image->nChannels);
  // cvCopy(image, smallImage, NULL);
  cvResetImageROI(image);
}

void Window::move(std::size_t x, std::size_t y) const {
  cvMoveWindow(_name.c_str(), x, y);
}

}
