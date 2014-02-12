
#include <highgui.h>
#include "utils/convert.hpp"
#include "utils/Log.hpp"
#include "brain/DataGenerator.hpp"

namespace brain {

DataGenerator::DataGenerator() {
  _json["dataDir"] = "."; // set the default directory to the current one
}

DataGenerator::~DataGenerator() {}

void DataGenerator::loadFromJson(std::string const &path) {
  _json.load(path);
}

void DataGenerator::saveToJson(std::string const &path) {
  LOG_DEBUG << "save to file " << path << LOG_ENDL;
  LOG_DEBUG << _json.str() << LOG_ENDL;
}

void DataGenerator::addImage(IplImage *image, std::string const &pattern) {
  std::string path = std::string(_json["dataDir"]) + "/" + pattern + "_" +
      utils::convert<std::string>(_json["patterns"][pattern].size()) + ".png";
  LOG_DEBUG << "add image " << path << " into data generator" << LOG_ENDL;
  // cvSaveImage(path.c_str(), image);
  _json["patterns"][pattern].push(path);
}

}
