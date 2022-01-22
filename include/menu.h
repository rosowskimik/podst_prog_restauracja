#ifndef __MENU_H__
#define __MENU_H__

#include <filesystem>
#include <string_view>
#include <vector>

#include "category.h"
#include "meal.h"

namespace fs = std::filesystem;

class Menu {
 public:
  using Categories = std::vector<Category>;

 private:
  Categories m_categories;
  fs::path m_directory;

 public:
  Menu() = default;

  /**
   * @brief Construct a new Menu object
   *
   * @param menu_path path to directory holding all Category files
   */
  Menu(fs::path menu_path);

  /**
   * @brief Returns a list of all Categories.
   *
   * @return const std::vector<Category>&
   */
  const Categories& categories() const;

  /**
   * @brief Returns the count of all Meals in Menu.
   *
   * @return const size_t
   */
  size_t size() const;

  /**
   * @brief Return a Meal at index.
   *
   * @param index index of meal to get
   * @return const Meal&
   * @warning This function will throw if index >= Menu::size()
   */
  const Meal& meal(size_t index) const;
};
#endif  // __MENU_H__