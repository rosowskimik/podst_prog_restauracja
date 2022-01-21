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
