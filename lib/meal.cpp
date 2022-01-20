#include "meal.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <string_view>

namespace fs = std::filesystem;

Meal::Meal(std::istream& input) {
  std::getline(input, m_name);

  std::string buffer;
  std::getline(input, buffer);
  m_price = std::stod(buffer);
}

Meal::Meal(std::string_view name, double price)
    : m_name(name), m_price(price) {}

bool Meal::operator==(const Meal& rhs) const {
  return m_name == rhs.m_name && m_price == rhs.m_price;
}

const std::string& Meal::name() const { return m_name; }

const double& Meal::price() const { return m_price; }

std::ostream& operator<<(std::ostream& os, const Meal& e) {
  os << e.m_name << '\n' << e.m_price;
  return os;
}