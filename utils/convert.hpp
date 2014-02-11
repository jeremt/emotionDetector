
#pragma once

#include <sstream>

namespace utils {

// Convert a value to another type.
template<typename To, typename From>
To convert(From const &from) {
  std::stringstream ss;
  To to;
  ss << from;
  ss >> to;
  return to;
}

}
