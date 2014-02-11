
#pragma once

#include <ostream>

namespace utils {

class Log {
 public:

  static Log out;
  static Log err;

  enum Level {
    kError,
    kWarning,
    kInfo,
    kDebug
  };
  enum EndLine {
    endl = 0xCACA
  };
  Log(std::ostream &stream);
  ~Log();
  void setLevel(Level level);
  Log &error();
  Log &warning();
  Log &info();
  Log &debug();

  // Output the given data into the Log stream.
  template<typename Type>
  Log &operator<<(Type const &type) {
    if (_currentLevel <= _maxLevel) {
      if (_isBegin) {
        _stream << _levelToString(_currentLevel);
        _isBegin = false;
      }
      _stream << type;
    }
    return *this;
  }

  Log &operator<<(EndLine) {
    if (_currentLevel <= _maxLevel) {
      _stream << "\e[m" << std::endl;
      _isBegin = true;
    }
    return *this;
  }

 private:
  std::string _levelToString(Level level);
  std::ostream &_stream;
  Level _maxLevel;
  Level _currentLevel;
  bool _isBegin;

};

// Some useful shortcuts
#define LOG_DEBUG utils::Log::out.debug()
#define LOG_INFO utils::Log::out.info()
#define LOG_WARN utils::Log::out.warning()
#define LOG_ERR utils::Log::out.error()
#define LOG_ENDL utils::Log::endl
#define LOG_LEVEL(level) do { utils::Log::out.setLevel(level); } while (false)

}  // namespace utils
