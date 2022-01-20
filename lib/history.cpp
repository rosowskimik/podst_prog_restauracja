#include "history.h"

#include <ctime>
#include <filesystem>
#include <fstream>
#include <optional>
#include <sstream>
#include <string_view>
#include <utility>

#include "order.h"

using uint = unsigned int;
namespace fs = std::filesystem;

History::History(fs::path history_path) : m_histfile(history_path) {
  if (fs::exists(history_path) && !fs::is_empty(history_path)) {
    std::fstream day_file(history_path, std::fstream::in);
    while (!day_file.eof() && day_file.peek() != '\0') {
      m_orders.push_back(std::move(Order(day_file)));
    }
  }
}

const History::Orders& History::orders() const { return m_orders; }

void History::save_order(const Order& order) {
  m_orders.insert(m_orders.begin(), std::move(order));

  writeToFile();
}

void History::writeToFile() const {
  std::fstream file(m_histfile, std::fstream::trunc | std::fstream::out);

  size_t counter = 1;

  for (const auto& order : m_orders) {
    file << order;
    if (counter != m_orders.size()) {
      file << '\n';
    }
    ++counter;
  }
}