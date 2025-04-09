#include "gtest/gtest.h"

// Include required headers from your forge-core module.
#include "scenario_forge.hpp"                   // Contains the ScenarioForge test runner.
#include "forgeable_scenario_provider.hpp"      // Provides getAll() for scenarios.
#include "forge_log.hpp"                        // Provides logging.
#include "test_config.hpp"                      // Test configuration DTO.
#include "forge_bench.hpp"                      // The test bench.
#include "abstract_forgeable_scenario.hpp"      // Base class for scenarios.
#include "forge_registrar.hpp"                  // The new header for ForgeRegistrar.

#include <memory>
#include <vector>
#include <string>

// --- Test Fixture for ScenarioForge ---

/**
 * @brief Test fixture for running forgeable scenarios.
 *
 * This fixture sets up the test configuration, creates the forge bench,
 * and initializes the forge registrar.
 */
class ScenarioForgeTest : public ::testing::Test {
protected:
    // Instance of our test runner.
    cppforge::scenarios::ScenarioForge scenarioForge;

    // Set up function which configures the test environment.
    void SetUp() override {
        cppforge::logging::ForgeLog::info("🧱 Setting up ScenarioForge test...");
        cppforge::logging::ForgeLog::debug("🔍 Loading test config...");

        // Create a dummy TestConfig.
        cppforge::scenarios::TestConfig config("TestProject", "features", 0, true);

        // Create the forge bench.
        cppforge::logging::ForgeLog::info("🛠 Creating forge bench...");
        auto bench = std::make_shared<cppforge::scenarios::ForgeBench>(config);

        // Run the setup specific to the ScenarioForge.
        scenarioForge.setUp();

        // Initialize the forge registrar with the forge bench.
        cppforge::core::registry::ForgeRegistrar::initialize(bench);
    }
};

// --- Test Case: Run All Forgeable Scenarios ---

/**
 * @brief Executes all registered Forgeable scenarios.
 *
 * This test case retrieves all available scenarios using the
 * ForgeableScenarioProvider and iterates through each scenario,
 * calling its smelt() method while logging progress and failures.
 */
TEST_F(ScenarioForgeTest, RunAllForgeableScenarios) {
    cppforge::logging::ForgeLog::info("🧲 Discovering all Forgeable scenario components...");
    auto scenarios = cppforge::scenarios::ForgeableScenarioProvider::getAll();

    cppforge::logging::ForgeLog::info("🔁 Running " + std::to_string(scenarios.size()) + " forgeable scenario(s)...");

    int index = 0;
    for (const auto& scenario : scenarios) {
        cppforge::logging::ForgeLog::info("🔥 [" + std::to_string(index) + "] Running scenario: " + scenario->scenarioName());
        try {
            scenario->smelt();
            cppforge::logging::ForgeLog::info("✅ [" + std::to_string(index) + "] Passed: " + scenario->scenarioName());
        } catch (const std::exception& e) {
            cppforge::logging::ForgeLog::error("❌ [" + std::to_string(index) + "] Failed: " + scenario->scenarioName() + " — " + std::string(e.what()));
            FAIL() << "Scenario failed with exception: " << e.what();
        }
        ++index;
    }

    cppforge::logging::ForgeLog::info("🏁 Scenario test run completed.");
}