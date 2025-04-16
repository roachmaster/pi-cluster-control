#include "print_bdd.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace cppforge::bdd {

    namespace fs = std::filesystem;

    void print_bdd_file(const fs::path& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "[ERROR] Could not open file: " << path << "\n";
            return;
        }

        std::string line;
        std::string section;

        std::cout << "=== " << path.filename() << " ===\n";

        while (std::getline(file, line)) {
            if (line.find("Scenario:") != std::string::npos) {
                std::cout << line << "\n";
            } else if (line.find("Given") != std::string::npos) {
                if (section != "SET_UP") {
                    std::cout << "\nSET_UP:\n";
                    section = "SET_UP";
                }
                std::cout << "  " << line << "\n";
            } else if (line.find("When") != std::string::npos) {
                if (section != "EXECUTE") {
                    std::cout << "\nEXECUTE:\n";
                    section = "EXECUTE";
                }
                std::cout << "  " << line << "\n";
            } else if (line.find("Then") != std::string::npos || line.find("And") != std::string::npos) {
                if (section != "VERIFY") {
                    std::cout << "\nVERIFY:\n";
                    section = "VERIFY";
                }
                std::cout << "  " << line << "\n";
            }
        }

        std::cout << std::endl;
    }

    void display_all_bdd(const std::string& directory) {
        for (const auto& entry : fs::recursive_directory_iterator(directory)) {
            if (entry.path().extension() == ".bdd") {
                print_bdd_file(entry.path());
            }
        }
    }

} // namespace cppforge::bdd