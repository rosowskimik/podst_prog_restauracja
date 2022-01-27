#include "order.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>

#include "meal.h"

using uint = unsigned int;

Order::Order() : m_meals(0) {
  // System time now.
  auto t = std::time(nullptr);
  // now -> date format
  auto tm = std::localtime(&t);

  // Random ID
  m_id.resize(15);
  std::mt19937 engine{std::random_device{}()};
  std::uniform_int_distribution<int> gen(33, 126);

  for (auto& c : m_id) {
    c = static_cast<char>(gen(engine));
  }

  // date format -> string
  std::stringstream date;
  date << std::put_time(tm, "%Y-%m-%d");
  m_date = date.str();
}

Order::Order(std::istream& in) : m_meals(0) {
  std::string buffer;

  // Date
  std::getline(in, m_date);

  // Id
  std::getline(in, m_id);

  // Length of orders meals
  std::getline(in, buffer);
  size_t length = std::stoul(buffer);
  buffer.clear();

  m_meals.reserve(length);

  // Foreach meal in length
  uint count = 0;
  for (; length > 0; --length) {
    // Meal at cursor
    Meal curr(in);

    // Meal's count
    std::getline(in, buffer);
    count = std::stoi(buffer);
    buffer.clear();

    m_meals[curr] = count;
  }
};

bool Order::operator==(const Order& rhs) const { return m_id == rhs.m_id; }

const std::string& Order::date() const { return m_date; }

const std::string& Order::id() const { return m_id; }

const Order::Entries& Order::entries() const { return m_meals; }

const size_t Order::meals_count() const { return m_meals.size(); }

const size_t Order::size() const {
  size_t size = 0;
  for (const auto& [_, count] : m_meals) {
    size += count;
  }
  return size;
}

const double Order::price_sum() const {
  double sum = 0;

  for (const auto& [entry, count] : m_meals) {
    sum += entry.price() * count;
  }

  return sum;
}

void Order::add_meal(const Meal& m) {
  // Try to find meal
  auto entry = m_meals.find(m);

  // If it was already added, just increment it's count
  if (entry != m_meals.end()) {
    entry->second += 1;
  } else {
    // Otherwise, add it with count = 1
    m_meals[m] = 1;
  }
}

void Order::remove_meal(size_t index) {
  // Get the iterator
  auto it = m_meals.begin();

  // Advance it to position at index
  std::advance(it, index);

  // If it's count is > 1
  if (it->second > 1) {
    // just decrement it
    --(it->second);
  } else {
    // Otherwise erase the element
    // ! Although this is an unordered_map, erasing an element still preserves
    //   the order of leftover elements
    //   (https://en.cppreference.com/w/cpp/container/unordered_map/erase)
    m_meals.erase(it);
  }
}

std::ostream& operator<<(std::ostream& os, const Order& o) {
  // Date\n
  // Id
  // Unique meals in order\n
  // Meal\n
  // meal's count
  size_t size = o.m_meals.size();
  os << o.m_date << '\n' << o.m_id << '\n' << size << '\n';
  for (const auto& [key, val] : o.m_meals) {
    os << key << '\n' << val;

    // If not at last meal, add newline
    if (size > 1) {
      os << '\n';
      --size;
    }
  }
  return os;
}
