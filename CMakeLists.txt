cmake_minimum_required(VERSION 2.8)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++0x")
project( FaceDetect )
find_package( OpenCV REQUIRED )

include_directories(.)

add_executable(

  FaceDetect

  src/main.cpp

  cvwrapper/Capture.cpp
  cvwrapper/Detector.cpp
  cvwrapper/Window.cpp
  cvwrapper/Image.cpp

  utils/loadCsv.cpp

  brain/Machine.cpp

)

target_link_libraries( FaceDetect ${OpenCV_LIBS} )
