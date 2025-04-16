#pragma once

#include <string>
#include <filesystem>

namespace cppforge::bdd {

void print_bdd_file(const std::filesystem::path& path);
void display_all_bdd(const std::string& directory);

}