#ifndef FORGE_BENCH_HPP
#define FORGE_BENCH_HPP

#include "test_config.hpp"  // Defines the TestConfig DTO.
#include "cppforge/core/forge/forge_log.hpp"    // Defines the logging class.
#include <string>
#include <utility>

namespace cppforge::scenarios {

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
            explicit ForgeBench(TestConfig  config)
                    : config_(std::move(config))
            {
                cppforge::logging::ForgeLog::info("🧰 ForgeBench initialized");
                cppforge::logging::ForgeLog::info("📂 Feature Directory: " + config_.featuresDirectory);
            }

            /**
             * @brief Retrieves the current test configuration.
             *
             * @return const TestConfig& The test configuration used to initialize ForgeBench.
             */
            [[nodiscard]] const TestConfig& getConfig() const { return config_; }

        private:
            // Test configuration stored by value.
            TestConfig config_;
        };

} // namespace cppforge

#endif // FORGE_BENCH_HPP