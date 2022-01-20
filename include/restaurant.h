#include <filesystem>
#include <string>

#include "menu.h"

namespace restaurant {
namespace fs = std::filesystem;

class Restaurant {
 private:
  std::string m_name;
  Menu m_menu;

 public:
  Restaurant(fs::path data_path);

  Menu& menu();
};
}  // namespace restaurant