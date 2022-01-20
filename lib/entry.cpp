#include "entry.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <string_view>

namespace restaurant {
namespace fs = std::filesystem;
using uint = unsigned int;

Entry::Entry(std::istream& input) {
  std::string buffer;

  std::getline(input, buffer);
  m_price = std::stoi(buffer);
  buffer.clear();

  std::getline(input, buffer);
  m_name.swap(buffer);
}

Entry::Entry(std::string_view name, uint price)
    : m_name(name), m_price(price) {}

const std::string& Entry::name() const { return m_name; }

const uint& Entry::price() const { return m_price; }

std::ostream& operator<<(std::ostream& os, const Entry& e) {
  os << e.m_price << '\n' << e.m_name << '\n';
  return os;
}
}  // namespace restaurant