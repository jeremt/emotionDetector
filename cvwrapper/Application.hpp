
#pragma once

#include "utils/Command.hpp"

namespace cvwrapper {

#define ESCAPE 27

// Implement from this abstract class to create an opencv application.
class Application {
public:

  // Default constructor.
  Application();

  // Empty destructor.
  virtual ~Application();

  // Run the opencv application.
  void run(utils::Command const &command);

  // Close the application.
  void close();

  // Set the keyWait time.
  void setKeyWait(float);

  virtual void onStart(utils::Command const &command) = 0;
  virtual void onEvent(int keycode) = 0;
  virtual void onUpdate() = 0;

private:
  bool _isOpen;
  float _keyWait;

};

} // namespace cvwrapper
