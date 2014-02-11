
#pragma once

namespace cvwrapper {

// Implement from this abstract class to create an opencv application.
class Application {
public:

  // Default constructor.
  Application();

  // Empty destructor.
  virtual ~Application();

  // Run the opencv application.
  void run();

  // Close the application.
  void close();

  // Set the keyWait time.
  void setKeyWait(float);

  virtual void onStart() = 0;
  virtual void onEvent(int keycode) = 0;
  virtual void onUpdate() = 0;

private:
  bool _isOpen;
  float _keyWait;

};

} // namespace cvwrapper
