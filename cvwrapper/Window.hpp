
#pragma once

#include <highgui.h>

namespace cvwrapper {

// Create a GUI window which can be moved, resized, and you can even draw
// many kind of things on it!
class Window {
public:

  // Create the window from its name.
  Window(std::string const &name);

  // Create and place the window.
  Window(std::string const &name, std::size_t x, std::size_t y);

  // Release the window.
  ~Window();

  // Display the given image on the window.
  void display(IplImage *image) const;

  // Draw the given |rect| on the image.
  void drawRect(IplImage *image, CvRect *rect, CvScalar const &color) const;

  // Draw the given |text| on the image.
  void drawText(IplImage *image,
                std::string const &text,
                CvPoint const &pt,
                CvScalar const &color) const;

  void drawImage(IplImage *image,
                 IplImage *smallImage,
                 std::size_t x,
                 std::size_t y);

  // Move the window on the screen.
  void move(std::size_t x, std::size_t y) const;

private:
  std::string _name;
  CvFont _font;

};

}
