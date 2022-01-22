#include "restaurant.h"

#include <filesystem>
#include <fstream>
#include <limits>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

std::string read_file(fs::path setup_file) {
  // Read setup file
  std::fstream setup(setup_file, std::fstream::in);

  // Ignore everything up to '='
  setup.ignore(std::numeric_limits<std::streamsize>::max(), '=');

  // Read leftover in line as restaurant name
  std::string name;
  std::getline(setup, name);
  return name;
}
