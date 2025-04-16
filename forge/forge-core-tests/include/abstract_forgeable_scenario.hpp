#ifndef ABSTRACT_FORGEABLE_SCENARIO_HPP
#define ABSTRACT_FORGEABLE_SCENARIO_HPP

#include <string>
#include "forgeable.hpp"  // Contains the definition of the Forgeable interface.

namespace cppforge::core::forge {

/**
 * @brief Abstract base class for all forgeable scenarios.
 *
 * AbstractForgeableScenario serves as the common base class for all scenarios
 * that are intended to be "forged" by the system. It extends the Forgeable interface
 * by requiring that derived classes implement:
 * - scenarioName(): a method that returns the name of the scenario.
 * - smelt(): a method that executes the core behavior of the scenario.
 *
 * @note Derived classes must override both pure virtual methods.
 */
    class AbstractForgeableScenario : public Forgeable {
    public:
        /**
         * @brief Retrieves the scenario name.
         *
         * This pure virtual method must be implemented by derived classes
         * to return the specific name of the scenario.
         *
         * @return std::string The scenario name.
         */
        [[nodiscard]] std::string scenarioName() const override = 0;

        /**
         * @brief Executes the core operation of the scenario.
         *
         * Derived classes must override this method to implement the functionality
         * that "smelts" (or processes) the scenario.
         */
        void smelt() override = 0;

        /**
         * @brief Virtual destructor.
         *
         * Ensures that the destructors of derived classes are properly called.
         * Marked noexcept for exception safety.
         */
        ~AbstractForgeableScenario() noexcept override {}
    };

} // namespace cppforge

#endif // ABSTRACT_FORGEABLE_SCENARIO_HPP