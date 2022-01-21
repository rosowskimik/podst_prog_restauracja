#ifndef __HISTORY_H__
#define __HISTORY_H__

#include <filesystem>
#include <functional>
#include <map>
#include <string>
#include <string_view>
#include <vector>

#include "order.h"

using uint = unsigned int;
namespace fs = std::filesystem;

class History {
 public:
  using Orders = std::vector<Order>;

 private:
  Orders m_orders;
  fs::path m_histfile;

  /**
   * @brief Save All Orders to a history file
   *
   */
  void writeToFile() const;

 public:
  History() = default;

  /**
   * @brief Construct a new History object
   *
   * @param history_path path to history file
   */
  History(fs::path history_path);

  /**
   * @brief Returns a list of Orders.
   *
   * @return const std::vector<Order>&
   */
  const Orders& orders() const;

  /**
   * @brief Saves the order to history file.
   *
   * @param order Order to save
   *
   * @see Order
   */
  void save_order(const Order& order);
};
#endif  // __HISTORY_H__