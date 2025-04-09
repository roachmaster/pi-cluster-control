#ifndef FORGEABLE_SCENARIO_PROVIDER_HPP
#define FORGEABLE_SCENARIO_PROVIDER_HPP

#include <memory>
#include <vector>
#include <string>
#include "abstract_forgeable_scenario.hpp"

namespace cppforge {
    namespace scenarios {

/**
 * @brief Provider for all registered AbstractForgeableScenario instances.
 *
 * ForgeableScenarioProvider is responsible for discovering and providing all
 * instances of AbstractForgeableScenario that have been registered in the system.
 * It serves a similar purpose to a service locator or registry for scenarios.
 *
 * @note The implementation of getAll() should return all available scenarios.
 */
        class ForgeableScenarioProvider {
        public:
            /**
             * @brief Retrieves all registered AbstractForgeableScenario instances.
             *
             * This static method returns a vector of shared pointers to AbstractForgeableScenario.
             * Each scenario is expected to be fully initialized and ready for use.
             *
             * @return std::vector<std::shared_ptr<AbstractForgeableScenario>> A vector containing all registered scenarios.
             */
            static std::vector<std::shared_ptr<cppforge::core::forge::AbstractForgeableScenario> > getAll();
        };

    } // namespace scenarios
} // namespace cppforge

#endif // FORGEABLE_SCENARIO_PROVIDER_HPP