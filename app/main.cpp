#include <iostream>
#include <string>

#include "restaurant.h"

// Test zapisu - odczytu do pliku
int main() {
  // Folder z menu znajduje się:
  Menu menu("data/menu");

  // Ścieżka do pliku z historią zamówień
  History historia("data/history.txt");

  // Wyciągnij nazwę restauracji z pliku
  std::string nazwa = get_name("data/setup.txt");
  std::cout << nazwa << '\n';

  std::cout << std::endl;

  // Wydrukuj wszystkie elementy Menu z podziałem na kategorie:
  // Dla wszystkich kategorii:
  for (const Category& category : menu.categories()) {
    // Wydrukuj nazwę kategorii:
    std::cout << "Kategoria: " << category.name() << '\n';
    // Dla wszystkich dań w danej kategorii:
    for (const Meal& meal : category.meals()) {
      // Wydrukuj nazwę
      std::cout << "Nazwa: " << meal.name() << '\n';
      // Oraz cenę:
      std::cout << "Cena: " << meal.price() << '\n';
    }
  }

  // Wypisz ilość wszystkich dań w Menu
  std::cout << "Rozmiar menu: " << menu.size() << '\n';

  std::cout << std::endl;

  // Utwórz nowe zamówienie
  Order new_order = menu.new_order();

  // Spróbuj wyciągnąć danie po indeksie
  // Zwraca to optional<Meal>,
  auto maybe_meal = menu.meal(0);

  // Który w ifie zwróci true jeżeli indeks mieści się w rozmiarze naszego menu:
  if (maybe_meal) {
    std::cout << "Danie istnieje\n";

    // Gdy mamy pewność, że indeks był w zasięgu (np w wyższym ifie
    // lub gdy jesteśmy pewni, że index < menu.size()),
    // możemy dostać się do tego dania przez wartość, jakby była wskaźnikiem:

    std::cout << "Jego nazwa to: " << maybe_meal->name() << '\n'
              << "A cena: " << maybe_meal->price() << '\n';

    // Dodaj danie do zamówienia
    new_order.add_meal(*maybe_meal);
    // Danie może się powtórzyć
    new_order.add_meal(*maybe_meal);

  } else {
    std::cout << "danie nie istnieje\n";
  }

  // Jeszcze pare innych dań (jeśli będziemy poza indeksem, to się wysypiemy)
  new_order.add_meal(*menu.meal(1));
  new_order.add_meal(*menu.meal(2));

  // Możemy przejrzeć wszystkie elementy w zamówieniu, wraz z ich ilością:
  for (const auto& [meal, count] : new_order.entries()) {
    // Nazwa : cena -> ilość
    std::cout << meal.name() << " : " << meal.price() << " -> " << count
              << '\n';
  }

  // Data zamówienia jest ustawiana automatycznie na dzisiejszą
  std::cout << new_order.date() << '\n';

  // Możemy wyciągnąć łączną kwotę do zapłaty za zamówienie
  std::cout << "Do zaplaty: " << new_order.price_sum() << '\n';

  // I na koniec zatwierdzić je, dodając je do historii zamówień
  historia.save_order(new_order);

  std::cout << std::endl;

  // Możemy przejrzeć historię zamówień:
  for (const Order& order : historia.orders()) {
    std::cout << "Dnia: " << order.date() << " placono: " << order.price_sum()
              << '\n';
  }

  return 0;
}