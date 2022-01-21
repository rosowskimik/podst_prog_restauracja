#ifndef __CATEGORY_H__
#define __CATEGORY_H__

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

namespace fs = std::filesystem;

class Meal;
class Menu;

class Category {
 public:
  using Meals = std::vector<Meal>;

 private:
  std::string m_name;
  Meals m_meals;
  fs::path m_file;

  friend Menu;

 public:
  Category() = default;

  /**
   * @brief Construct a new Category object
   *
   * @param category_path path to a file, from which to load this category
   */
  Category(fs::path category_path);

  /**
   * @brief Get Category name
   *
   * @return const std::string&
   */
  const std::string& name() const;

  /**
   * @brief Get Category's Meals.
   *
   * @return const std::vector<Meal>&
   */
  const Meals& meals() const;
};
#endif  // __CATEGORY_H__