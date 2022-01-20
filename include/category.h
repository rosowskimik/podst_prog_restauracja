#ifndef __CATEGORY_H__
#define __CATEGORY_H__

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

namespace restaurant {
namespace fs = std::filesystem;
using uint = unsigned int;

class Entry;
class Menu;

class Category {
 private:
  std::string m_name;
  std::vector<Entry> m_entries;
  fs::path m_file;

  friend Menu;

 public:
  Category() = default;

  Category(fs::path category_path);

  const std::string& name() const;
  const std::vector<Entry>& entries() const;

  void add_entry(std::string_view entry_name, uint entry_price);

  void writeToFile() const;
};
}  // namespace restaurant
#endif  // __CATEGORY_H__