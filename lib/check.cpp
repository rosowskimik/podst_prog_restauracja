#include <cstdlib>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void check_path_exists(const fs::path& to_check) {
  fs::path curr;
  for (const auto& el : to_check) {
    curr /= el;
    if (!fs::exists(curr)) {
      std::cerr << "Sciezka '" << curr.string() << "' nie istnieje\n";
      std::exit(EXIT_FAILURE);
    }
  }
}

void check_path_not_empty(const fs::path& to_check) {
  if (fs::is_empty(to_check)) {
    std::cerr << "Sciezka '" << to_check.string() << "' jest pusta\n";
    std::exit(EXIT_FAILURE);
  }
}

void check_path_is_file(const fs::path& to_check) {
  if (!fs::is_regular_file(to_check)) {
    std::cerr << "Sciezka '" << to_check.string() << "' nie jest plikiem\n";
    std::exit(EXIT_FAILURE);
  }
}

void check_path_is_directory(const fs::path& to_check) {
  if (!fs::is_directory(to_check)) {
    std::cerr << "Sciezka '" << to_check.string() << "' nie jest katalogiem\n";
    std::exit(EXIT_FAILURE);
  }
}