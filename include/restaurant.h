#include <filesystem>
#include <string>

#include "history.h"
#include "menu.h"

namespace fs = std::filesystem;

/**
 * @brief Load name
 *
 * @param setup_file path to setup file
 * @return std::string
 */
std::string read_file(fs::path setup_file);

void printWelcomeMsg();
void printMainMenu(const std::string descriptions[],
                   const int descriptionsCount);
void printDots(int filledSpace, int maxDotsToPrint = 30);
std::string getFilledString(char fillingSymbol, int filledSpace, int max = 50);
void printRestaurantMenuEntry(int id, std::string name, double price);
void printRestaurantMenu(Menu& menu);
void printCurrentOrder(Order& currOrder);
void printOrderHistoryRow(int id, Order orderData);
void printOrderHistory(const std::vector<Order>& orderHistoryData);