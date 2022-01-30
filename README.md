# Projekt zaliczeniowy "Restauracja" - Podstawy programowania

![Preview](assets/preview.gif)

## Opis
Projekt zaliczeniowy z przedmiotu podstawy programowania.
Aplikacja konsolowa pozwalająca na wyświetlanie menu restauracji, tworzenie zamówień i przegląd ich historii.

Folder `example_data` zawiera strukturę plików, która jest wykorzystywana przez aplikację. Aby je wykorzystać, należy zmienić nazwę folderu z `example_data` na `data`.

Aplikacja jest dostępna do pobrania [tutaj](https://github.com/rosowskimik/podst_prog_restauracja/releases).

Szczegóły dotyczące samej obsługi aplikacji są dostępne w [instrukcji](assets/instrukcja.pdf).

## Budowa z kodu źródłowego

Do budowy kodu będzie potrzebny [CMake](https://cmake.org/download/) minimum w wersji 3.16 oraz kompilator c++ zgodny ze standardem [c++17](https://en.cppreference.com/w/cpp/17).

Przykładowa konfiguracja i budowa aplikacji ze źródła:

1. Sklonuj repozytorium:

    * `git clone https://github.com/rosowskimik/podst_prog_restauracja.git`

2. Skonfiguruj i zbuduj aplikację:

    * `cd podst_prog_restauracja`

    * `cmake -S . -B build -G <generator> [opcje]`

        Powszechne generatory to m.in:

        * `Ninja` --- do generowania plików [Ninja](https://ninja-build.org).
        * `Unix Makefiles` --- do generowania plików kompatybilnych z make'iem.
        * `Visual Studio` --- do generowania projektów i solucji Visual Studio.
        * `Xcode` --- do generowania projektów Xcode.

        Powszechne opcje to m.in:

        * `DCMAKE_BUILD_TYPE=typ`  --- Poprawne opcje dla *typ*u: Debug, Release, RelWithDebInfo i MinSizeRel.

    * `cmake --build build [-- [opcje]]` lub bezpośrednio jeden z wyżej wymienionych generatorów.

    * Po więcej szczegółów na temat wykorzystania CMake'a proszę patrzeć na stronę jego [dokumentacji](https://cmake.org/documentation/).

## Autorzy

Autorami aplikacji i związanymi z nią materiałami są:
* Dawid Sekula
* Kacper Janas
* Łukasz Kwaśniewski
* Mikołaj Rosowski
* Wojtek Pestka