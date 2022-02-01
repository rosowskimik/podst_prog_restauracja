#include "restaurant.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include "check.h"

namespace fs = std::filesystem;

std::string read_file(fs::path setup_file) {
  // Check if file exists, refers to regular file && isn't expty
  check_path_exists(setup_file);
  check_path_is_file(setup_file);
  check_path_not_empty(setup_file);

  std::fstream setup(setup_file, std::fstream::in);
  std::string buffer;

  // Read up to '=' sign.
  std::getline(setup, buffer, '=');

  // Normalize input (doesn't matter if name/Name/NAME, etc.)
  std::transform(buffer.begin(), buffer.end(), buffer.begin(),
                 [](auto c) { return std::tolower(c); });
  // If setup file is malformed, throw
  if (buffer != "name") {
    std::cerr << "Problem z plikiem setup.txt (spodziewano sie "
                 "name=<nazwa restauracji>)\n";
    std::exit(EXIT_FAILURE);
  }
  buffer.clear();

  // Read leftover in line as restaurant name
  std::getline(setup, buffer);
  return buffer;
}

void printDashedLine(std::string text, int lineWidth) {
  lineWidth -= (text.length());
  for (int i = 0; i < lineWidth / 2; i++) std::cout << "-";

  std::cout << text;

  for (int i = 0; i < lineWidth / 2; i++) std::cout << "-";

  std::cout << std::endl;
}

void printWelcomeMsg() {
  std::string nazwa = read_file("data/setup.txt");
  printDashedLine("", 52);
  std::cout << nazwa << std::endl;
  printDashedLine("", 52);
  std::cout << "Witaj w programie Restauracja 1.0" << std::endl;
  std::cout << std::endl;
};

void printMainMenu(const std::string descriptions[],
                   const int descriptionsCount) {
  std::cout << std::endl << "Opcje:" << std::endl;
  for (int x = 0; x < descriptionsCount; x++) {
    std::cout << "[" << x << "] " << descriptions[x] << std::endl;
  }
}

void printDots(int filledSpace, int maxDotsToPrint) {
  for (int j = 0; j < maxDotsToPrint - filledSpace; j++) std::cout << ".";
}

std::string getFilledString(char fillingSymbol, int filledSpace, int max) {
  std::string filledString;

  for (int i = 0; i < max - filledSpace; i++) {
    filledString += fillingSymbol;
  }

  return filledString;
}

void printRestaurantMenuEntry(int id, std::string name, double price) {
  std::cout << "|\t";
  std::cout << id << ". " << name;

  int filledSpace = name.length();
  if (id < 10) filledSpace -= 1;
  printDots(filledSpace);

  std::cout << std::setfill('0') << std::setw(5) << std::fixed
            << std::setprecision(2) << price;
  std::cout << "    |" << std::endl;
}

void printRestaurantMenu(Menu& menu) {
  printDashedLine(" MENU ", 52);
  int id = 1;
  for (const Category& category : menu.categories()) {
    // Wydrukuj nazwę kategorii:
    std::cout << "|" << getFilledString(' ', 0) << "|" << std::endl;
    std::cout << "|\t" << category.name()
              << getFilledString(' ', category.name().length() + 7) << "|"
              << std::endl;

    // Dla wszystkich dań w danej kategorii:
    for (const Meal& meal : category.meals()) {
      printRestaurantMenuEntry(id, meal.name(), meal.price());
      id++;
    }
  }
  std::cout << "|" << getFilledString(' ', 0) << "|" << std::endl;
  printDashedLine("", 52);
}

void printCurrentOrder(Order& currOrder) {
  std::cout << std::endl;
  std::cout << "Wybrano łącznie " << currOrder.size() << " dań: " << std::endl;
  int i = 1;
  for (const auto& [meal, count] : currOrder.entries()) {
    std::cout << "\t - [" << i++ << "] " << meal.name();
    printDots(meal.name().length());
    std::cout << " x" << count << " = " << std::setfill('0') << std::setw(5)
              << std::fixed << std::setprecision(2) << meal.price() * count
              << std::endl;
  }
  std::cout << std::endl;
  std::cout << "Suma:  " << currOrder.price_sum();
  std::cout << std::endl;
}

void printOrderHistoryRow(int id, Order orderData) {
  printDashedLine("-", 107);
  auto iter = orderData.entries().begin();
  std::cout << "|    "
            // numer
            << std::setfill('0') << std::setw(2) << id
            << " | "
            // data
            << orderData.date()
            << "  | "
            // Id
            << orderData.id()
            << " | "
            // miejszce na nazwę dania (32 - dóugoóóDania)
            << iter->first.name() << std::fixed << std::setprecision(2)
            << getFilledString(' ', iter->first.name().length(), 32)
            << "| "
            // cena
            << std::setfill('0') << std::setw(5) << iter->first.price()
            << " | "
            // ile razy danie zostało zamówione
            << iter->second
            << "  | "
            // cena razy ilość
            << std::setfill('0') << std::setw(5)
            << iter->first.price() * iter->second << "    |     - |"
            << std::endl;
  for (iter++; iter != orderData.entries().end(); iter++) {
    auto& [meal, count] = *iter;
    std::cout << "|    "
              // numer
              << getFilledString(' ', 0, 2)
              << " | "
              // data
              << getFilledString(' ', 0, 10)
              << "  | "
              // Id
              << getFilledString(' ', 0, 15)
              << " | "
              // miejszce na nazwę dania (32 - długośćDania)
              << meal.name() << getFilledString(' ', meal.name().length(), 32)
              << "| "
              // cena
              << std::fixed << std::setprecision(2) << std::setfill('0')
              << std::setw(5) << meal.price()
              << " | "
              // ile razy danie zostało zamówione
              << count
              << "  | "
              // cena razy ilość
              << std::setfill('0') << std::setw(5) << meal.price() * count
              << "    |     - |" << std::endl;
  }
  std::cout << "|    "
            // numer
            << getFilledString(' ', 0, 2)
            << " | "
            // data
            << getFilledString(' ', 0, 10)
            << "  | "
            // Id
            << getFilledString(' ', 0, 15)
            << " | "
            // miejszce na nazwę dania (32 - długośćDania)
            << getFilledString(' ', 0, 32)
            << "| "
            // cena
            << getFilledString(' ', 0, 5)
            << " | "
            // ile razy danie zostało zamówione
            << getFilledString(' ', 0, 1)
            << "  | "
            // cena razy ilość
            << getFilledString(' ', 0, 5) << "    | " << std::setfill('0')
            << std::setw(5) << std::fixed << std::setprecision(2)
            << orderData.price_sum() << " |" << std::endl;
}

void printOrderHistory(const std::vector<Order>& orderHistoryData) {
  // nagłówek

  std::cout << std::endl;
  printDashedLine("-", 107);
  std::string historymenu(
      "|     # | Data        | Id              | Dania "
      "                          | Cena  | N  | C * N    |  Suma |");
  std::cout << historymenu << std::endl;
  // koniec nagłówka
  double order_sum = 0;
  for (int i = 0; i < orderHistoryData.size(); i++) {
    printOrderHistoryRow(i + 1, orderHistoryData[i]);
    order_sum += orderHistoryData[i].price_sum();
  }
  printDashedLine("-", 107);
  std::stringstream sum_string;
  sum_string << "SUMA: " << std::fixed << std::setprecision(2) << order_sum;
  std::cout << "|" << getFilledString(' ', 0, 104 - sum_string.str().length())
            << sum_string.str() << " |" << std::endl;
  printDashedLine("-", 107);
}