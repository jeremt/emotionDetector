
#pragma once

#include <cv.h>

namespace cvwrapper {

// Crop the given image to a smallest one according the given coefs.
IplImage *ajustImage(IplImage *image,
                    CvRect *roi,
                    float widthCoef = 0.7,
                    float heightCoef = 0.6);

// Equalize the image.
IplImage *equalizeImage(IplImage *image);

}  // namespace cvwrapper
