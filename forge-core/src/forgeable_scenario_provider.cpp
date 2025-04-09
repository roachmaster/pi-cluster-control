#include "forgeable_scenario_provider.hpp"
#include "abstract_forgeable_scenario.hpp" // Your abstract scenario header.
#include "forge_registry.hpp"              // The registry header.
#include "forge_log.hpp"                   // The logging class.

#include <exception>
#include <memory>
#include <string>
#include <vector>

namespace cppforge {
    namespace scenarios {

        std::vector<std::shared_ptr<AbstractForgeableScenario>> ForgeableScenarioProvider::getAll() {
            cppforge::logging::ForgeLog::info("🔎 Resolving AbstractForgeableScenario implementations from ForgeRegistry...");

            // Retrieve all forges that can produce AbstractForgeableScenario instances.
            auto matchingForges = cppforge::core::registry::ForgeRegistry::instance().getAllAssignableTo<AbstractForgeableScenario>();

            std::vector<std::shared_ptr<AbstractForgeableScenario>> scenarios;

            for (size_t index = 0; index < matchingForges.size(); ++index) {
                try {
                    // Use the forge to create an instance.
                    std::unique_ptr<cppforge::core::forge::Forgeable> instance = matchingForges[index]->create();
                    // Attempt to cast the instance to AbstractForgeableScenario.
                    AbstractForgeableScenario* scenarioRaw = dynamic_cast<AbstractForgeableScenario*>(instance.get());
                    if (scenarioRaw) {
                        // Transfer ownership to a shared_ptr.
                        std::shared_ptr<AbstractForgeableScenario> scenarioPtr(std::move(instance));
                        cppforge::logging::ForgeLog::info("✅ Found scenario: " + scenarioPtr->scenarioName());
                        scenarios.push_back(scenarioPtr);
                    }
                } catch (const std::exception& e) {
                    cppforge::logging::ForgeLog::error("❌ Failed to create scenario instance — " + std::string(e.what()));
                }
            }
            return scenarios;
        }

    } // namespace scenarios
} // namespace cppforge