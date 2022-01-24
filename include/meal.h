#ifndef __ENTRY_H__
#define __ENTRY_H__

#include <functional>
#include <iostream>
#include <string>
#include <string_view>

class Meal {
 private:
  std::string m_name;
  double m_price;

 public:
  Meal() = default;

  /**
   * @brief Construct a new Meal object
   *
   * @param input an input stream to load this Meal from
   */
  Meal(std::istream& input);

  bool operator==(const Meal& rhs) const;

  /**
   * @brief Get Meal name
   *
   * @return const std::string&
   */
  const std::string& name() const;

  /**
   * @brief Get Meal price
   *
   * @return const double&
   */
  const double& price() const;

  friend std::ostream& operator<<(std::ostream& os, const Meal& e);
};

// Hash implementation for using Meal as a hashed key.
namespace std {
template <>
struct hash<Meal> {
  std::size_t operator()(const Meal& e) const {
    std::size_t h1 = std::hash<std::string>{}(e.name());
    std::size_t h2 = std::hash<double>{}(e.price());
    return h1 ^ (h2 << 1);
  };
};
}  // namespace std
#endif  // __ENTRY_H__