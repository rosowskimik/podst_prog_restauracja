#include "menu.h"

#include <filesystem>
#include <string_view>
#include <utility>
#include <vector>

#include "category.h"

namespace restaurant {
namespace fs = std::filesystem;

Menu::Menu(fs::path menu_path) : m_directory(menu_path) {
  for (const auto& file : fs::directory_iterator(menu_path)) {
    if (file.is_regular_file()) {
      m_categories.push_back(std::move(Category(file)));
    }
  }
}

const std::vector<Category>& Menu::categories() const { return m_categories; }

const Entry& Menu::entry(size_t index) const {
  for (const auto& category : m_categories) {
    if (category.entries().size() > index) {
      return category.entries()[index];
    } else {
      index -= category.entries().size();
    }
  }
}

Category& Menu::add_category(std::string_view category_name) {
  Category new_category{};

  new_category.m_name = category_name;
  new_category.m_file = m_directory / category_name;
  new_category.writeToFile();

  m_categories.push_back(std::move(new_category));
  return m_categories.back();
}
}  // namespace restaurant