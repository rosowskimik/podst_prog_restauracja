#include "history.h"

#include <ctime>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string_view>
#include <utility>

#include "order.h"

using uint = unsigned int;
namespace fs = std::filesystem;

History::History(fs::path history_path) : m_histfile(history_path) {
  // check If file exists
  if (fs::exists(history_path) && fs::is_regular_file(history_path)) {
    std::fstream day_file(history_path, std::fstream::in);

    // While cursor not at eof or one before
    while (!day_file.eof() && day_file.peek() != '\0') {
      // Load orders into memory
      m_orders.emplace_back(day_file);
    }
  }
}

const History::Orders& History::orders() const { return m_orders; }

void History::save_order(const Order& order) {
  // Orders are saved in history from newest to oldest
  // So new orders are added at the beginning
  m_orders.insert(m_orders.begin(), std::move(order));

  writeToFile();
}

void History::writeToFile() const {
  // Create / Truncate history file
  std::fstream file(m_histfile, std::fstream::trunc | std::fstream::out);

  size_t counter = 1;

  // For each order
  for (const auto& order : m_orders) {
    // Save it in file
    file << order;
    // If we're not at the last order
    if (counter < m_orders.size()) {
      // Add newline
      file << '\n';
    }
    ++counter;
  }
}