#include <filesystem>
#include <string>

#include "history.h"
#include "menu.h"

namespace fs = std::filesystem;

std::string get_name(fs::path setup_file);
