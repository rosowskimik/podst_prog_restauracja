
#include <iostream>
#include <string>

#include "restaurant.h"

Menu menu("data/menu");
History history("data/orders.txt");

void printError(const std::string errorMsg) {
  std::cout << std::endl << " > " << errorMsg << std::endl << std::endl;
}

int getOption(std::string msg, int min, int max) {
  int result;

  std::cout << msg;
  std::cin >> result;

  if (result > max || result < min) return -1;

  return result;
}

void handleOrderAdd(Order& ord) {
  printRestaurantMenu(menu);
  std::cout
      << "Proszę podać numery id dań jakie mają zostać dodane do zamówienia,"
      << "\nwpisanie 0 spowoduje przejście do następnego kroku." << std::endl;

  std::cout << std::endl;

  int option;

  // Handle order input
  while (true) {
    option = getOption("Proszę podać numer id dania: ", 0, menu.size());

    if (option == 0)
      break;
    else if (option == -1) {
      printError("Proszę podać poprawne id dania");
    } else {
      ord.add_meal(menu.meal(option - 1));
    }

    if (ord.size() >= 10) break;
  }
}

void handleOrderRemove(Order& ord) {
  std::cout
      << std::endl
      << "Proszę podać numery id dań jakie mają zostać usunięte z zamówienia,"
      << "\nwpisanie 0 spowoduje przejście do następnego kroku." << std::endl;

  std::cout << std::endl;

  int option;

  // Handle order input
  while (true) {
    printCurrentOrder(ord);

    option = getOption("Proszę podać numer id dania do usunięcia: ", 0,
                       ord.entries().size());

    if (option == 0)
      break;
    else if (option == -1) {
      printError("Proszę podać poprawne id dania");
    } else {
      ord.remove_meal(option - 1);
    }

    if (ord.size() <= 0) break;
  }
}

int handleRestaurantMenu() {
  Order new_order;
  handleOrderAdd(new_order);

  int option;

  bool handlingOrder = true;

  static const std::string avOptions[] = {
      "Potwierdź zamówienie", "Usuń dania z zamówienia",
      "Dodaj dania do zamówienia", "Anuluj zamówienie"};

  static const int optionsCount = sizeof(avOptions) / sizeof(avOptions[0]);

  // Handle after order summary input
  while (handlingOrder) {
    printCurrentOrder(new_order);

    printMainMenu(avOptions, optionsCount);

    option = getOption("Proszę wybrać opcję: ", 0, optionsCount - 1);

    switch (option) {
      case -1:
        printError("Proszę wybrać poprawną opcję");
        break;

      case 0:
        handlingOrder = false;
        break;

      case 1:
        handleOrderRemove(new_order);
        break;

      case 2:
        handleOrderAdd(new_order);
        break;

      case 3:
        return 1;

      default:
        printError("Coś poszło nie tak");
        break;
    }
  }

  if (new_order.size()) history.save_order(new_order);

  return 0;
}

int handleHistory() {
  std::cout << std::endl;
  std::cout << "Lista zamówień [" << history.orders().size() << "]";
  printOrderHistory(history.orders());
  return 0;
}

bool isDateValid(std::string date) {
  if (date.size() != 10) return false;
  try {
    std::string year = date.substr(0, 4);
    std::string month = (date.substr(5, 2));
    std::string day = (date.substr(8, 2));
    int year_int = std::stoi(year);
    int month_int = stoi(month);
    int day_int = stoi(day);

    if (!((month_int > 0) && ((month_int <= 12)))) return false;
    if (!((day_int > 0) && ((day_int <= 31)))) return false;

  } catch (...) {
    return false;
  }
  return true;
}
int handleHistoryWithDate() {
  std::vector<Order> history_for_date;
  std::string inputDate;

  std::cout << "Podaj datę [YYYY-MM-DD]:";
  std::cin >> inputDate;
  if (isDateValid(inputDate)) {
    std::string year = (inputDate.substr(0, 4));
    std::string month = (inputDate.substr(5, 2));
    std::string day = (inputDate.substr(8, 2));

    for (auto& order : history.orders()) {
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
  } else {
    printError("Błędny format daty");
    return handleHistoryWithDate();
  }
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
      std::cout << "Podano 0 - program kończy działanie" << std::endl;
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