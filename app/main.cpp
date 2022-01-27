
#include <iostream>
#include <string>

#include "restaurant.h"

Menu menu("data/menu");
History history("data/orders.txt");

void printError(const std::string errorMsg) {
  std::cout << std::endl << " > " << errorMsg << std::endl;
}

int getOption(std::string msg, int min, int max) {
  int result;

  std::cout << msg;
  std::cin >> result;

  if (result > max || result < min) return -1;

  return result;
}

int handleRestaurantMenu() {
  Order new_order;
  printRestaurantMenu(menu);
  std::cout
      << "Proszę podać numery id dań jakie mają zostać dodane do zamówienia,"
      << "\nwpisanie 0 spowoduje przejście do następnego kroku." << std::endl;

  std::cout << std::endl;

  // Handle order input
  while (true) {
    const int option =
        getOption("Proszę podać numer id dania: ", 0, menu.size());

    if (option == 0) break;
    if (option == -1) {
      printError("Proszę podać poprawne id dania");
    } else
      new_order.add_meal(menu.meal(option - 1));
  }

  printCurrentOrder(new_order);

  // Handle after order summary input
  // Handle empty order

  history.save_order(new_order);

  return 0;
}

int handleHistory() {
  std::cout << std::endl;
  std::cout << "Lista zamówień [" << history.orders().size() << "]";
  printOrderHistory(history.orders());
  return 0;
}

int handleHistoryWithDate() {
  std::vector<Order> history_for_date;
  std::string inputDate;

  std::cout << "Podaj datę [YYYY-MM-DD]:";
  std::cin >> inputDate;

  std::string year = (inputDate.substr(0, 4));
  std::string month = (inputDate.substr(5, 2));
  std::string day = (inputDate.substr(8, 2));

  for (auto order : history.orders()) {
    if (order.date() == inputDate) {
      history_for_date.push_back(order);
    }
  }

  std::cout << std::endl;
  std::cout << "Lista zamówień [" << history_for_date.size() << "/"
            << history.orders().size()
            << " spełnia wymaganie data: " << inputDate << "]:" << std::endl;
  printOrderHistory(history_for_date);
  return 0;
}

int executeMenuOption(int option) {
  switch (option) {
    case 1:
      return handleRestaurantMenu();
    case 2:
      return handleHistory();
    case 3:
      return handleHistoryWithDate();
    default:
      printError("W tym menu nie ma takiej opcji!");
      return 1;
  }
}

int handleMenu() {
  static const std::string avOptions[] = {"Zamknij program", "Złóż zamówienia",
                                          "Historia zamówień",
                                          "Historia zamówień dla danego dnia"};

  static const int optionsCount = sizeof(avOptions) / sizeof(avOptions[0]);

  while (true) {
    printMainMenu(avOptions, optionsCount);
    const int option = getOption("Proszę wybrać opcję: ", 0, optionsCount - 1);

    if (option == 0) {
      std::cout << "Podano 0 - program kończy działanie";
      return 0;
    } else {
      executeMenuOption(option);
    }
  }
}

int main() {
  printWelcomeMsg();

  handleMenu();
}