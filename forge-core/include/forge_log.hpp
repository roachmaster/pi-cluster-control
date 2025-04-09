#ifndef FORGE_LOG_HPP
#define FORGE_LOG_HPP

#include <iostream>
#include <string>

namespace cppforge {
    namespace logging {

        class ForgeLog {
        public:
            static void info(const std::string& msg) {
                std::cout << "[INFO] " << msg << "\n";
            }

            static void debug(const std::string& msg) {
                std::cout << "[DEBUG] " << msg << "\n";
            }

            static void error(const std::string& msg) {
                std::cerr << "[ERROR] " << msg << "\n";
            }

            static void warn(const std::string& msg) {
                std::cout << "[WARN] " << msg << "\n";
            }
        };

    } // namespace logging
} // namespace cppforge

#endif // FORGE_LOG_HPP