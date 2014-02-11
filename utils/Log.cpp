
#include <iostream>
#include "utils/Log.hpp"

namespace utils {

Log Log::out(std::cout);
Log Log::err(std::cerr);

Log::Log(std::ostream &stream)
    : _stream(stream),
      _maxLevel(kInfo),
      _currentLevel(kInfo),
      _isBegin(true) {}

Log::~Log() {}

void Log::setLevel(Level level) {
  _maxLevel = level;
}

Log &Log::error() {
  _currentLevel = kError;
  return *this;
}

Log &Log::warning() {
  _currentLevel = kWarning;
  return *this;
}

Log &Log::info() {
  _currentLevel = kInfo;
  return *this;
}

Log &Log::debug() {
  _currentLevel = kDebug;
  return *this;
}

std::string Log::_levelToString(Log::Level level) {
  switch (level) {
    case kError:   return "\e[31m[Error] ";
    case kWarning: return "\e[33m[Warning] ";
    case kInfo:    return "\e[32m[Info] ";
    case kDebug:   return "\e[34m[Debug] ";
  }
  return "Unknown";
}

}  // namspace utils
