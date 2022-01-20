#ifndef __MENU_H__
#define __MENU_H__

#include <filesystem>
#include <string_view>
#include <vector>

#include "category.h"
#include "entry.h"

namespace restaurant {
namespace fs = std::filesystem;

class Menu {
 private:
  std::vector<Category> m_categories;
  fs::path m_directory;

 public:
  Menu() = default;

  Menu(fs::path menu_path);

  const std::vector<Category>& categories() const;

  const Entry& entry(size_t index) const;

  Category& add_category(std::string_view category_name);
};
}  // namespace restaurant
#endif  // __MENU_H__