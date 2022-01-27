#include "restaurant.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

std::string read_file(fs::path setup_file) {
  // Read setup file
  std::fstream setup(setup_file, std::fstream::in);

  // Ignore everything up to '='
  setup.ignore(std::numeric_limits<std::streamsize>::max(), '=');

  // Read leftover in line as restaurant name
  std::string name;
  std::getline(setup, name);
  return name;
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
    // Wydrukuj nazwó kategorii:
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
  printDashedLine("-", 90);
  auto iter = orderData.entries().begin();
  std::cout << "|    "
            // numer
            << std::setfill('0') << std::setw(2) << id
            << " | "
            // data
            << orderData.date()
            << "  | "
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
    auto [meal, count] = *iter;
    std::cout << "|    "
              // numer
              << getFilledString(' ', 0, 2)
              << " | "
              // data
              << getFilledString(' ', 0, 10)
              << "  | "
              // miejszce na nazwę dania (32 - długośćDania)
              << meal.name() << getFilledString(' ', meal.name().length(), 32)
              << "| "
              // cena
              << std::setfill('0') << std::setw(5) << std::fixed
              << std::setprecision(2) << meal.price()
              << " | "
              // ile razy danie zostało zamówione
              << count
              << "  | "
              // cena razy ilość
              << meal.price() * count << "    |     - |" << std::endl;
  }
  std::cout << "|    "
            // numer
            << getFilledString(' ', 0, 2)
            << " | "
            // data
            << getFilledString(' ', 0, 10)
            << "  | "
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
  printDashedLine("-", 90);
  std::string historymenu(
      "|     # | Data        | Dania "
      "                          | Cena  | N  | C * N    |  Suma |");
  std::cout << historymenu << std::endl;
  // koniec nagłówka
  double order_sum = 0;
  for (int i = 0; i < orderHistoryData.size(); i++) {
    printOrderHistoryRow(i + 1, orderHistoryData[i]);
    order_sum += orderHistoryData[i].price_sum();
  }
  printDashedLine("-", 90);
  std::stringstream sum_string;
  sum_string << "SUMA: " << std::fixed << std::setprecision(2) << order_sum;
  std::cout << "|" << getFilledString(' ', 0, 86 - sum_string.str().length())
            << sum_string.str() << " |" << std::endl;
  printDashedLine("-", 90);
}