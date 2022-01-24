#include "category.h"

#include <filesystem>
#include <fstream>
#include <istream>
#include <utility>
#include <vector>

#include "check.h"
#include "meal.h"

namespace fs = std::filesystem;

Category::Category(fs::path category_path)
    : m_name(category_path.stem().string()), m_file(category_path) {
  // Check if path refers to regular file && it isn't empty
  check_path_is_file(category_path);
  check_path_not_empty(category_path);

  std::ifstream file(category_path, std::fstream::in);

  // While cursor not at eof
  // Load it's contents into memory, until eof.
  while (!file.eof()) {
    m_meals.emplace_back(file);
  }
}

const std::string& Category::name() const { return m_name; }

const Category::Meals& Category::meals() const { return m_meals; }