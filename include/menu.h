#ifndef __MENU_H__
#define __MENU_H__

#include <filesystem>
#include <optional>
#include <string_view>
#include <vector>

#include "category.h"
#include "meal.h"
#include "order.h"

namespace fs = std::filesystem;

class Menu {
 private:
  std::vector<Category> m_categories;
  fs::path m_directory;

 public:
  Menu() = default;

  /**
   * @brief Construct a new Menu object
   *
   * @param menu_path path to directory holding all menu files
   */
  Menu(fs::path menu_path);

  /**
   * @brief Returns a vector of all categories.
   *
   * @return const std::vector<Category>&
   */
  const std::vector<Category>& categories() const;

  /**
   * @brief Returns the count of all Meals in Menu.
   *
   * @return const size_t
   */
  size_t size() const;

  std::optional<const Meal> meal(size_t index) const;

  /**
   * @brief Create new order
   *
   * @return Order
   */
  Order new_order() const;

  // Category& add_category(std::string_view category_name);
};
#endif  // __MENU_H__