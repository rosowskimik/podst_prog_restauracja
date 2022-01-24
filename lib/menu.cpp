#include "menu.h"

#include <cassert>
#include <filesystem>
#include <string_view>
#include <utility>
#include <vector>

#include "category.h"
#include "check.h"

namespace fs = std::filesystem;

Menu::Menu(fs::path menu_path) : m_directory(menu_path) {
  // Check if path exists, refers to directory && isn't empty
  check_path_exists(menu_path);
  check_path_is_directory(menu_path);
  check_path_not_empty(menu_path);

  for (const auto& file : fs::directory_iterator(menu_path)) {
    // Check if path refers to file
    check_path_is_file(file);

    m_categories.emplace_back(file);
  }
}

const std::vector<Category>& Menu::categories() const { return m_categories; }

const Meal& Menu::meal(size_t index) const {
  assert(index <= size());

  // For all categories
  for (const auto& category : m_categories) {
    // if index is < categories meals
    if (index < category.meals().size()) {
      // We're in correct category, return it's meal at index
      return category.meals()[index];
    } else {
      // Otherwise decrement index by category's size
      index -= category.meals().size();
    }
  }
  // Unreachable!
}

size_t Menu::size() const {
  size_t size = 0;

  for (const auto& c : m_categories) {
    size += c.meals().size();
  }

  return size;
}