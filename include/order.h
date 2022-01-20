#ifndef __ORDER_H__
#define __ORDER_H__

#include <iostream>
#include <unordered_map>

#include "meal.h"

using uint = unsigned int;

class Order {
 public:
  using Meals = std::unordered_map<Meal, uint>;

 private:
  std::string m_date;
  Meals m_meals;

 public:
  Order();

  Order(std::istream& in);

  bool operator==(const Order& rhs) const;

  /**
   * @brief Get order date
   *
   * @return const std::string&
   */
  const std::string& date() const;

  /**
   * @brief Get order entries
   *
   *
   * @return const Entries& (Meal -> Count)
   */
  const Meals& entries() const;

  /**
   * @brief Returns the price of all entries in order.
   *
   * @return const uint
   */
  const double price_sum() const;

  /**
   * @brief Adds a Meal to an Order
   *
   * @param m A Meal to add example: order.add_meal(*menu.meal(0));
   */
  void add_meal(const Meal& m);

  friend std::ostream& operator<<(std::ostream& os, const Order& o);
};
#endif  // __ORDER_H__