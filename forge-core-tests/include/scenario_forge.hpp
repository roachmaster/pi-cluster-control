#ifndef SCENARIO_FORGE_HPP
#define SCENARIO_FORGE_HPP

#include <memory>
#include <string>

namespace cppforge {
    namespace scenarios {

// Forward declarations of classes used in the test runner.
        class ForgeBench;
        class TestConfig;
        class ForgeableScenario;

/**
 * ScenarioForge is a reusable test runner for running all Forgeable scenarios.
 * It mirrors the Kotlin class by performing setup, then executing scenarios.
 */
        class ScenarioForge {
        public:
            ScenarioForge();
            virtual ~ScenarioForge() = default;

            // Performs the necessary setup.
            virtual void setUp();

            // Runs all discovered Forgeable scenarios.
            virtual void runAllForgeableScenarios();

        protected:
            // A pointer to our ForgeBench (factory bench). Replace with your actual class.
            std::shared_ptr<ForgeBench> forgeBench_;
        };

    } // namespace scenarios
} // namespace cppforge

#endif // SCENARIO_FORGE_HPP