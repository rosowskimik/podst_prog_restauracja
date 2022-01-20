#ifndef __ENTRY_H__
#define __ENTRY_H__

#include <filesystem>
#include <iostream>
#include <string>
#include <string_view>

namespace restaurant {
namespace fs = std::filesystem;
using uint = unsigned int;

class Entry {
 private:
  std::string m_name;
  uint m_price;

 public:
  Entry() = default;

  Entry(std::istream& input);

  Entry(std::string_view name, uint price);

  const std::string& name() const;
  const uint& price() const;

  friend std::ostream& operator<<(std::ostream& os, const Entry& e);
};
}  // namespace restaurant
#endif  // __ENTRY_H__