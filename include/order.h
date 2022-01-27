#ifndef __ORDER_H__
#define __ORDER_H__

#include <iostream>
#include <unordered_map>

#include "meal.h"

using uint = unsigned int;

class Order {
 public:
  using Entries = std::unordered_map<Meal, uint>;

 private:
  std::string m_date;
  std::string m_id;
  Entries m_meals;

 public:
  Order();

  bool operator==(const Order& rhs) const;

  /**
   * @brief Construct a new Order object
   *
   * @param input an input stream to load this Order from
   */
  Order(std::istream& input);

  /**
   * @brief Get Order's date
   *
   * @return const std::string&
   */
  const std::string& date() const;

  const std::string& id() const;

  /**
   * @brief Get Order's Meals
   *
   * @return const std::unordered_map<Meal, unsigned int>&
   */
  const Entries& entries() const;

  /**
   * @brief Get Order's unique meals count
   *
   * @return const size_t
   */
  const size_t meals_count() const;

  /**
   * @brief Get Order's meals count
   *
   * @return const size_t
   */
  const size_t size() const;

  /**
   * @brief Returns the price of all Meals in order.
   *
   * @return const double
   */
  const double price_sum() const;

  /**
   * @brief Adds a Meal to an Order
   *
   * @param m a Meal to add
   * @see Meal
   * @see Menu::meal(index)
   */
  void add_meal(const Meal& m);

  /**
   * @brief Decrement the count of Meal entry at index
   *
   * @param index index of entry
   */
  void remove_meal(size_t index);

  friend std::ostream& operator<<(std::ostream& os, const Order& o);
};
#endif  // __ORDER_H__
