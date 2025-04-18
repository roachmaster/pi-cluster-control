#ifndef DUMMY_SCENARIO_HPP
#define DUMMY_SCENARIO_HPP

#include "abstract_forgeable_scenario.hpp"  // Defines AbstractForgeableScenario.
#include "cppforge/core/forge/forge_log.hpp"                    // Provides logging.

#include <memory>
#include <string>

namespace cppforge::scenarios {

//------------------------------------------------------------------------------
// Dummy Scenario for Testing
//------------------------------------------------------------------------------

// DummyScenario implements AbstractForgeableScenario.
// This class serves as a test tool for demonstrating scenario registration and execution.
    class DummyScenario : public cppforge::core::forge::AbstractForgeableScenario {
    public:
        DummyScenario() : name_("DummyScenario"), smelted_(false) {}

        // Returns the scenario's name.
        [[nodiscard]] std::string scenarioName() const override {
            return name_;
        }

        // Performs a dummy "smelt" operation, which logs a message and sets a flag.
        void smelt() override {
            smelted_ = true;
            cppforge::logging::ForgeLog::info("DummyScenario::smelt() executed.");
        }

        // Helper method to verify that smelt() was executed.
        [[nodiscard]] bool wasSmelted() const {
            return smelted_;
        }

    private:
        std::string name_;
        bool smelted_;
    };

} // namespace cppforge::scenarios

#endif // DUMMY_SCENARIO_HPP