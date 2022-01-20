#include "restaurant.h"

#include <filesystem>
#include <fstream>
#include <limits>
#include <sstream>
#include <string>

#include "menu.h"

namespace fs = std::filesystem;

std::string get_name(fs::path setup_file) {
  std::fstream setup(setup_file, std::fstream::in);

  setup.ignore(std::numeric_limits<std::streamsize>::max(), '=');

  std::string name;
  std::getline(setup, name);
  return name;
}
