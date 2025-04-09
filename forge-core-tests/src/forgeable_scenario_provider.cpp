#include "forgeable_scenario_provider.hpp"
#include "abstract_forgeable_scenario.hpp"  // Provides the definition of AbstractForgeableScenario.
#include "forge_registry.hpp"              // Provides access to the global registry.
#include "forge_log.hpp"                   // Provides logging.
#include <vector>
#include <memory>
#include <exception>
#include <string>

namespace cppforge::scenarios {

    /**
     * @brief Retrieves all registered AbstractForgeableScenario instances.
     *
     * This function queries the global ForgeRegistry for all forges that can create instances
     * assignable to AbstractForgeableScenario. For each forge, it attempts to create an instance.
     * If successful, the instance is added to the returned vector.
     *
     * @return A vector of shared pointers to AbstractForgeableScenario objects.
     */
    std::vector<std::shared_ptr<cppforge::core::forge::AbstractForgeableScenario>>
    ForgeableScenarioProvider::getAll() {
        cppforge::logging::ForgeLog::info("🔎 Resolving AbstractForgeableScenario implementations from ForgeRegistry...");

        // Retrieve all forges capable of producing AbstractForgeableScenario instances.
        auto matchingForges = cppforge::core::registry::ForgeRegistry::instance().getAllAssignableTo<cppforge::core::forge::AbstractForgeableScenario>();

        std::vector<std::shared_ptr<cppforge::core::forge::AbstractForgeableScenario>> scenarios;

        for (auto &forge : matchingForges) {
            try {
                // Create an instance using the forge.
                std::unique_ptr<cppforge::core::forge::Forgeable, cppforge::core::forge::NoOpDeleter> instance = forge->create();
                // Convert the unique_ptr to a shared_ptr. We use a custom no-op deleter in the shared_ptr as well,
                // so that ownership is not transferred (lifetime is managed elsewhere).
                auto sharedInst = std::shared_ptr<cppforge::core::forge::Forgeable>(instance.get(), cppforge::core::forge::NoOpDeleter{});
                // Attempt to downcast to AbstractForgeableScenario.
                auto scenarioPtr = std::dynamic_pointer_cast<cppforge::core::forge::AbstractForgeableScenario>(sharedInst);
                if (scenarioPtr) {
                    cppforge::logging::ForgeLog::info("✅ Found scenario: " + scenarioPtr->scenarioName());
                    scenarios.push_back(scenarioPtr);
                }
            } catch (const std::exception &e) {
                cppforge::logging::ForgeLog::error("❌ Failed to create scenario instance — " + std::string(e.what()));
            }
        }

        return scenarios;
    }

} // namespace cppforge::scenarios