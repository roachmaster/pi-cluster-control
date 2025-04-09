#ifndef SCENARIO_FORGE_HPP
#define SCENARIO_FORGE_HPP

#include <memory>
#include <string>
#include "forge_log.hpp"  // For logging purposes.

namespace cppforge::scenarios {

    // Forward declarations of classes used in the test runner.
    class ForgeBench;
    class TestConfig;
    class ForgeableScenario;

    /**
     * @brief ScenarioForge is a reusable test runner for running all Forgeable scenarios.
     *
     * It mirrors the Kotlin class by performing setup, then executing scenarios.
     */
    class ScenarioForge {
    public:
        ScenarioForge();

        virtual ~ScenarioForge() = default;

        /**
         * @brief Performs the necessary setup.
         *
         * This implementation simply logs that the setup has been called.
         * Extend as needed for your test environment.
         */
        virtual void setUp();

        /**
         * @brief Runs all discovered Forgeable scenarios.
         *
         * Minimal placeholder implementation. You can expand this method to
         * iterate through and run your scenarios.
         */
        virtual void runAllForgeableScenarios();

    protected:
        // A pointer to our ForgeBench (factory bench). Replace with your actual class.
        std::shared_ptr<ForgeBench> forgeBench_;
    };

    // Inline definitions

    inline ScenarioForge::ScenarioForge() {
        // Minimal construction logic. Log if needed.
        cppforge::logging::ForgeLog::debug("ScenarioForge constructed.");
    }

    inline void ScenarioForge::setUp() {
        // Minimal setup logic. For now, we just log the call.
        cppforge::logging::ForgeLog::info("ScenarioForge::setUp() called.");
        // Optionally, you could create and store a ForgeBench instance here.
    }

    inline void ScenarioForge::runAllForgeableScenarios() {
        // Minimal placeholder implementation. In a full implementation you might:
        // - Retrieve all Forgeable scenarios,
        // - Iterate and run their functionality,
        // - Log results, etc.
        cppforge::logging::ForgeLog::info("ScenarioForge::runAllForgeableScenarios() called.");
    }

} // namespace cppforge::scenarios

#endif // SCENARIO_FORGE_HPP