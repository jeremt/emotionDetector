
#pragma once

namespace utils {

// Inherit from this class to make your class non copyable.
class NonCopyable {
public:
  virtual ~NonCopyable() {}
private:
  NonCopyable(NonCopyable const &other);
  NonCopyable &operator=(NonCopyable const &other);
};

}
