#include "forge_registrar.hpp"
#include "forge_registry.hpp"
#include "include/dummy_scenario.hpp"  // Contains the DummyScenarioForge definition.
#include "include/dummy_scenario_forge.hpp"  // Contains the DummyScenarioForge definition.
#include "cppforge/core/forge/forge_log.hpp"

#include <memory>

namespace cppforge::core::registry {

    void ForgeRegistrar::initialize(const std::shared_ptr<cppforge::scenarios::ForgeBench> &bench) {
        cppforge::logging::ForgeLog::info("Initializing ForgeRegistry via Test Registrar...");

        // Create a stub implementation for the dummy scenario.
        // For this test, we use a shared_ptr to a DummyScenario.
        auto stub = std::make_shared<cppforge::scenarios::DummyScenario>();
        // We leave the default implementation as null (i.e. nullptr) so that the DummyScenarioForge
        // always returns the stub instance.
        std::shared_ptr<cppforge::scenarios::DummyScenario> defaultImpl = nullptr;

        // Create a new DummyScenarioForge with the specified implementations.
        auto dummyForge = std::make_shared<cppforge::scenarios::DummyScenarioForge>(defaultImpl, stub);

        // Register the DummyScenario factory for DummyScenario instances.
        ForgeRegistry::instance().registerForge<cppforge::scenarios::DummyScenario>(dummyForge);

        cppforge::logging::ForgeLog::info("DummyScenarioForge successfully registered by Test Registrar.");
    }
} // namespace cppforge