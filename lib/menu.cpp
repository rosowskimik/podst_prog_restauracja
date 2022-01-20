#include "menu.h"

#include <filesystem>
#include <optional>
#include <string_view>
#include <utility>
#include <vector>

#include "category.h"
#include "order.h"

namespace fs = std::filesystem;

Menu::Menu(fs::path menu_path) : m_directory(menu_path) {
  for (const auto& file : fs::directory_iterator(menu_path)) {
    if (file.is_regular_file()) {
      m_categories.push_back(std::move(Category(file)));
    }
  }
}

const std::vector<Category>& Menu::categories() const { return m_categories; }

std::optional<const Meal> Menu::meal(size_t index) const {
  for (const auto& category : m_categories) {
    if (category.meals().size() > index) {
      return std::optional(category.meals()[index]);
    } else {
      index -= category.meals().size();
    }
  }
  return std::nullopt;
}

size_t Menu::size() const {
  size_t size = 0;

  for (const auto& c : m_categories) {
    size += c.meals().size();
  }

  return size;
}

Order Menu::new_order() const { return Order{}; }

// Category& Menu::add_category(std::string_view category_name) {
//   Category new_category{};

//   new_category.m_name = category_name;
//   new_category.m_file = m_directory / category_name;
//   new_category.writeToFile();

//   m_categories.push_back(std::move(new_category));
//   return m_categories.back();
// }