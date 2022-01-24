#include "restaurant.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include "check.h"

namespace fs = std::filesystem;

std::string read_file(fs::path setup_file) {
  // Check if file exists, refers to regular file && isn't expty
  check_path_exists(setup_file);
  check_path_is_file(setup_file);
  check_path_not_empty(setup_file);

  std::fstream setup(setup_file, std::fstream::in);
  std::string buffer;

  // Read up to '=' sign.
  std::getline(setup, buffer, '=');

  // Normalize input (doesn't matter if name/Name/NAME, etc.)
  std::transform(buffer.begin(), buffer.end(), buffer.begin(),
                 [](auto c) { return std::tolower(c); });
  // If setup file is malformed, throw
  if (buffer != "name") {
    std::cerr << "Problem z plikiem setup.txt (spodziewano sie "
                 "name=<nazwa restauracji>)\n";
    std::exit(EXIT_FAILURE);
  }
  buffer.clear();

  // Read leftover in line as restaurant name
  std::getline(setup, buffer);
  return buffer;
}
