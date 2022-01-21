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
std::string load_name(fs::path setup_file);
