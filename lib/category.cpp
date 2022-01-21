#include "category.h"

#include <filesystem>
#include <fstream>
#include <istream>
#include <utility>
#include <vector>

#include "meal.h"

namespace fs = std::filesystem;

Category::Category(fs::path category_path)
    : m_name(category_path.stem().string()), m_file(category_path) {
  // If file isn't empty
  if (!fs::is_empty(category_path)) {
    std::ifstream file(category_path, std::fstream::in);

    // While cursor not at eof
    // Load it's contents into memory, until eof.
    while (!file.eof()) {
      m_meals.emplace_back(file);
    }
  }
}

const std::string& Category::name() const { return m_name; }

const Category::Meals& Category::meals() const { return m_meals; }