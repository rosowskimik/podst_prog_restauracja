#ifndef __ENTRY_H__
#define __ENTRY_H__

#include <filesystem>
#include <functional>
#include <iostream>
#include <string>
#include <string_view>

namespace fs = std::filesystem;

class Meal {
 private:
  std::string m_name;
  double m_price;

 public:
  Meal() = default;

  Meal(std::istream& input);

  Meal(std::string_view name, double price);

  bool operator==(const Meal& rhs) const;

  /**
   * @brief Get meals name
   *
   * @return const std::string&
   */
  const std::string& name() const;

  /**
   * @brief Get meals price
   *
   * @return const uint&
   */
  const double& price() const;

  friend std::ostream& operator<<(std::ostream& os, const Meal& e);
};

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