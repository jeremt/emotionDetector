cmake_minimum_required(VERSION 2.8.8)

project(emotionDetector)

# Settings

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++0x")
find_package(OpenCV REQUIRED)

include_directories(.)

include_directories(libs)

set(

  SOURCES

  cvwrapper/Capture.cpp
  cvwrapper/Detector.cpp
  cvwrapper/Window.cpp
  cvwrapper/Image.cpp

  utils/loadCsv.cpp

  brain/Machine.cpp

)

add_library(OBJECTS OBJECT ${SOURCES})

# OpenCV application

add_executable(emotionDetector src/main.cpp $<TARGET_OBJECTS:OBJECTS>)

target_link_libraries(emotionDetector ${OpenCV_LIBS})

# Some unit tests

add_executable(testMachine tests/machine.cpp $<TARGET_OBJECTS:OBJECTS>)
target_link_libraries(testMachine ${OpenCV_LIBS})
