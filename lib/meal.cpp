#include "meal.h"

#include <iostream>
#include <string>
#include <string_view>

Meal::Meal(std::istream& input) {
  // Meal name
  std::getline(input, m_name);

  // Meal price
  std::string buffer;
  std::getline(input, buffer);
  m_price = std::stod(buffer);
}

bool Meal::operator==(const Meal& rhs) const {
  return m_name == rhs.m_name && m_price == rhs.m_price;
}

const std::string& Meal::name() const { return m_name; }

const double& Meal::price() const { return m_price; }

std::ostream& operator<<(std::ostream& os, const Meal& e) {
  os << e.m_name << '\n' << e.m_price;
  return os;
}