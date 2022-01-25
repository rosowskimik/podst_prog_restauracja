#ifndef __CHECK_H__
#define __CHECK_H__

#include <filesystem>

namespace fs = std::filesystem;

void check_path_exists(const fs::path& to_check);

void check_path_not_empty(const fs::path& to_check);

void check_path_is_file(const fs::path& to_check);

void check_path_is_directory(const fs::path& to_check);
#endif // __CHECK_H__
