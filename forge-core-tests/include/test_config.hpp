#ifndef TEST_CONFIG_HPP
#define TEST_CONFIG_HPP

#include <string>
#include <sstream>
#include <iomanip>

namespace cppforge {
    namespace scenarios {

/**
 * @brief Data Transfer Object (DTO) for test configuration.
 *
 * This class stores configuration details used during testing, such as the project name,
 * the directory of features, the expected number of scenarios, and a flag indicating whether
 * verbose logging is enabled.
 */
        class TestConfig {
        public:
            /// The name of the project.
            std::string projectName;

            /// The directory where feature files are located.
            std::string featuresDirectory;

            /// The expected number of test scenarios.
            int expectedScenarioCount;

            /// Flag to enable or disable verbose logging.
            bool enableVerboseLogging;

            /**
             * @brief Default constructor.
             *
             * Initializes all members with default values.
             */
            TestConfig()
                    : projectName(""), featuresDirectory(""), expectedScenarioCount(0), enableVerboseLogging(false) { }

            /**
             * @brief Parameterized constructor.
             *
             * @param projName The project name.
             * @param featuresDir The directory of feature files.
             * @param expectedCount The expected number of scenarios.
             * @param verbose Flag to enable verbose logging.
             */
            TestConfig(const std::string& projName, const std::string& featuresDir, int expectedCount, bool verbose)
                    : projectName(projName), featuresDirectory(featuresDir), expectedScenarioCount(expectedCount), enableVerboseLogging(verbose) { }

            /**
             * @brief Returns a string representation of the TestConfig.
             *
             * Formats the configuration details into a multi-line string similar to the Kotlin toString() method.
             *
             * @return std::string A formatted string representing the test configuration.
             */
            std::string toString() const {
                std::ostringstream oss;
                oss << "Test Configuration:\n"
                    << " • Project Name: " << projectName << "\n"
                    << " • Features Dir: " << featuresDirectory << "\n"
                    << " • Expected Scenarios: " << expectedScenarioCount << "\n"
                    << " • Verbose Logging: " << std::boolalpha << enableVerboseLogging;
                return oss.str();
            }
        };

    } // namespace scenarios
} // namespace cppforge

#endif // TEST_CONFIG_HPP