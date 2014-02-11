
#include "cvwrapper/Window.hpp"

namespace cvwrapper {

Window::Window(std::string const &name) :
  _name(name) {
  cvNamedWindow(_name.c_str(), CV_WINDOW_AUTOSIZE);
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


void Window::move(std::size_t x, std::size_t y) const {
  cvMoveWindow(_name.c_str(), x, y);
}

}
