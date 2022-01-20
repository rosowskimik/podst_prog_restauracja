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
 private:
  std::string m_name;
  std::vector<Meal> m_entries;
  fs::path m_file;

  friend Menu;

 public:
  Category() = default;

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
  const std::vector<Meal>& meals() const;

  // void add_entry(std::string_view entry_name, uint entry_price);

  // void writeToFile() const;
};
#endif  // __CATEGORY_H__