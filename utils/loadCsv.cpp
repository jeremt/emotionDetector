
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "utils/loadCsv.hpp"

namespace utils {

CsvData loadCsv(std::string const &path, char delim) {
  std::ifstream file(path);
  CsvData data;
  std::string row;
  if (!file.is_open())
    throw std::runtime_error("unable to load csv \"" + path + "\"");
  while (std::getline(file, row)) {
    std::size_t offset;
    if (!row.empty() && (offset = row.find(delim)) != std::string::npos) {
      data.push_back(std::make_pair(
          row.substr(0, offset),
          row.substr(offset + 1)));
    }
  }
  return data;
}

}

