
#pragma once

#include <stdexcept>
#include <map>
#include <vector>
#include "utils/convert.hpp"

namespace utils {

// Handle command-line arguments.
class Command {
 public:
  Command();

  ~Command();

  bool parse(int argc, char **argv);

  inline Command &setDescription(std::string const &description) {
    _description = description;
    return *this;
  }

  inline Command &setSynopsis(std::string const &synopsis) {
    _synopsis = synopsis;
    return *this;
  }

  template<typename Type>
  Command &addOpt(std::string const &name,
                     Type const &value,
                     std::string const &help = "") {
    _options[name] = convert<std::string>(value);
    _optionsDesc[name] = help;
    return *this;
  }

  template<typename Type>
  Type getOpt(std::string const &name) const {
    if (_options.find(name) == _options.end())
      throw std::runtime_error("unknown option " + name + ".");
    return convert<Type>(_options.at(name));
  }

  template<typename Type>
  std::string const &getArg(size_t i) const {
    if (i >= _args.size())
      throw std::out_of_range(
        "too few arguments (`" + _name + " help` for more infos).");
    return _args[i];
  }

 private:

  void _displayHelp(std::string const &name);

  std::map<std::string, std::string> _options;
  std::map<std::string, std::string> _optionsDesc;
  std::vector<std::string> _args;
  std::string _name;
  std::string _description;
  std::string _synopsis;
};

}
