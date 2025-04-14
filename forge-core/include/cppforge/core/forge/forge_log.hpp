#ifndef FORGE_LOG_HPP
#define FORGE_LOG_HPP

#include <iostream>
#include <string>

namespace cppforge::logging {

    class ForgeLog {
    public:
        static void info(const std::string &msg) {
            std::cout << "\033[32m[INFO] " << msg << "\033[0m" << "\n";
        }

        static void debug(const std::string &msg) {
            std::cout << "\033[34m[DEBUG] " << msg << "\033[0m" << "\n";
        }

        static void error(const std::string &msg) {
            std::cerr << "\033[31m[ERROR] " << msg << "\033[0m" << "\n";
        }

        static void warn(const std::string &msg) {
            std::cout << "\033[33m[WARN] " << msg << "\033[0m" << "\n";
        }
    };

} // namespace cppforge::logging

#endif // FORGE_LOG_HPP