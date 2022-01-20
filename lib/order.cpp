#include "order.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "meal.h"

using uint = unsigned int;

Order::Order() : m_meals(0) {
  auto t = std::time(nullptr);
  auto tm = std::localtime(&t);

  std::stringstream date;
  date << std::put_time(tm, "%Y-%m-%d");
  m_date = date.str();
}

Order::Order(std::istream& in) : m_meals(0) {
  std::string buffer;

  std::getline(in, m_date);

  std::getline(in, buffer);
  size_t length = std::stoul(buffer);
  buffer.clear();

  m_meals.reserve(length);

  uint count = 0;
  for (; length > 0; --length) {
    Meal curr(in);

    std::getline(in, buffer);
    count = std::stoi(buffer);
    buffer.clear();

    m_meals[curr] = count;
  }
};

bool Order::operator==(const Order& rhs) const {
  return m_meals == rhs.m_meals;
}

const std::string& Order::date() const { return m_date; }

const Order::Meals& Order::entries() const { return m_meals; }

const double Order::price_sum() const {
  double sum = 0;

  for (const auto& [entry, count] : m_meals) {
    sum += entry.price() * count;
  }

  return sum;
}

void Order::add_meal(const Meal& m) {
  auto entry = m_meals.find(m);
  if (entry != m_meals.end()) {
    entry->second += 1;
  } else {
    m_meals[m] = 1;
  }
}

std::ostream& operator<<(std::ostream& os, const Order& o) {
  size_t size = o.m_meals.size();
  os << o.m_date << '\n' << size << '\n';
  for (const auto& [key, val] : o.m_meals) {
    os << key << '\n' << val;
    if (size > 1) {
      os << '\n';
      --size;
    }
  }
  return os;
}