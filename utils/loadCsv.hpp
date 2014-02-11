
#pragma once

#include <vector>
#include <string>
#include <utility>

namespace utils {

typedef std::pair<std::string, std::string> CsvRow;
typedef std::vector<CsvRow> CsvData;

CsvData loadCsv(std::string const &path, char delim = ':');

}
