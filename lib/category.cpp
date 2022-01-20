#include "category.h"

#include <filesystem>
#include <fstream>
#include <istream>
#include <utility>
#include <vector>

#include "entry.h"

namespace restaurant {
namespace fs = std::filesystem;

Category::Category(fs::path category_path)
    : m_name(category_path.stem().string()), m_file(category_path) {
  std::ifstream file(category_path, std::fstream::in);

  while (file.peek() != ';') {
    m_entries.push_back(std::move(Entry(file)));
  }
}

const std::string& Category::name() const { return m_name; }

const std::vector<Entry>& Category::entries() const { return m_entries; }

void Category::add_entry(std::string_view entry_name, uint entry_price) {
  m_entries.emplace_back(entry_name, entry_price);
  writeToFile();
}

void Category::writeToFile() const {
  std::fstream file(m_file, std::fstream::trunc | std::fstream::out);

  for (const auto& entry : m_entries) {
    file << entry;
  }
  file << ';';
}
}  // namespace restaurant