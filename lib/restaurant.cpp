#include "restaurant.h"

#include <filesystem>
#include <fstream>
#include <limits>
#include <sstream>
#include <string>

#include "menu.h"

namespace restaurant {
namespace fs = std::filesystem;

Restaurant::Restaurant(fs::path data_path) : m_menu(data_path / "menu") {
  std::fstream setup(data_path / "setup.txt", std::fstream::in);

  setup.ignore(std::numeric_limits<std::streamsize>::max(), '=');
  std::getline(setup, m_name);
}

Menu& Restaurant::menu() { return m_menu; }
}  // namespace restaurant
