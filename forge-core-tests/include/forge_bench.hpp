#ifndef FORGE_BENCH_HPP
#define FORGE_BENCH_HPP

#include "test_config.hpp"  // Defines the TestConfig DTO.
#include "forge_log.hpp"    // Defines the logging class.
#include <string>

namespace cppforge {
    namespace scenarios {

/**
 * @brief ForgeBench serves as the factory bench or context for running scenarios.
 *
 * ForgeBench is initialized with a TestConfig instance. Its constructor logs essential information,
 * such as confirmation that it has been initialized and the feature directory from the configuration.
 */
        class ForgeBench {
        public:
            /**
             * @brief Constructs a ForgeBench instance.
             *
             * @param config The TestConfig instance containing configuration details.
             */
            explicit ForgeBench(const TestConfig& config)
                    : config_(config)
            {
                cppforge::logging::ForgeLog::info("🧰 ForgeBench initialized");
                cppforge::logging::ForgeLog::info("📂 Feature Directory: " + config_.featuresDirectory);
            }

            /**
             * @brief Retrieves the current test configuration.
             *
             * @return const TestConfig& The test configuration used to initialize ForgeBench.
             */
            const TestConfig& getConfig() const { return config_; }

        private:
            // Test configuration stored by value.
            TestConfig config_;
        };

    } // namespace scenarios
} // namespace cppforge

#endif // FORGE_BENCH_HPP