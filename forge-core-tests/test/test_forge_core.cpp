#include "gtest/gtest.h"

// Include necessary headers.
#include "test_config.hpp"                      // Defines TestConfig DTO.
#include "abstract_forgeable_scenario.hpp"      // Defines AbstractForgeableScenario.
#include "forge_registry.hpp"                   // Defines the global ForgeRegistry.
#include "forgeable_scenario_provider.hpp"      // Provides getAll() for scenarios.
#include "forge_log.hpp"                        // Provides logging.

#include <memory>
#include <string>

using namespace cppforge::scenarios;
using namespace cppforge::core::forge;
using namespace cppforge::core::registry;
using namespace cppforge::logging;

//------------------------------------------------------------------------------
// Dummy Scenario and Factory for Testing
//------------------------------------------------------------------------------

// DummyScenario implements AbstractForgeableScenario.
// In a real scenario, this would have actual logic.
class DummyScenario : public AbstractForgeableScenario {
public:
    DummyScenario() : name_("DummyScenario"), smelted_(false) {}

    virtual std::string scenarioName() const override {
        return name_;
    }

    virtual void smelt() override {
        // For testing, simply mark that the scenario was "smelted".
        smelted_ = true;
        ForgeLog::info("DummyScenario::smelt() executed.");
    }

    bool wasSmelted() const {
        return smelted_;
    }
private:
    std::string name_;
    bool smelted_;
};

// DummyScenarioForge is a factory that always returns a DummyScenario instance.
class DummyScenarioForge : public Forge<DummyScenario> {
public:
    virtual std::unique_ptr<DummyScenario> createImpl() override {
        return std::make_unique<DummyScenario>();
    }
};

//------------------------------------------------------------------------------
// Tests
//------------------------------------------------------------------------------

// Test that verifies that TestConfig's toString() method produces a string containing expected values.
TEST(TestConfigTest, ToStringContainsExpectedValues) {
    // Create a sample TestConfig.
    TestConfig config("MyProject", "my_features", 5, true);
    std::string output = config.toString();

    // Verify that the output contains specific substrings.
    EXPECT_NE(output.find("MyProject"), std::string::npos);
    EXPECT_NE(output.find("my_features"), std::string::npos);
    EXPECT_NE(output.find("5"), std::string::npos);
    EXPECT_NE(output.find("true"), std::string::npos);
}

// Test that registers a dummy scenario factory and then retrieves it via the registry and provider.
TEST(ForgeRegistryTest, RegisterAndRetrieveDummyScenario) {
    // First, clear the registry to ensure a clean slate.
    ForgeRegistry::instance().clear();

    // Create a dummy factory instance.
    std::shared_ptr<DummyScenarioForge> dummyForge = std::make_shared<DummyScenarioForge>();

    // Register the dummy scenario factory for DummyScenario.
    ForgeRegistry::instance().registerForge<DummyScenario>(dummyForge);

    // Retrieve the factory directly from the registry.
    auto retrievedForge = ForgeRegistry::instance().get<DummyScenario>();
    EXPECT_NE(retrievedForge, nullptr);

    // Use the retrieved factory to create a scenario instance.
    std::unique_ptr<Forgeable> instance = retrievedForge -> create();
    DummyScenario* dummyInstance = dynamic_cast<DummyScenario*>(instance.get());
    ASSERT_NE(dummyInstance, nullptr) << "Retrieved instance is not a DummyScenario.";

    // Now retrieve scenarios using the ForgeableScenarioProvider.
    auto scenarios = ForgeableScenarioProvider::getAll();
    // For this test, we expect to get at least one scenario.
    EXPECT_FALSE(scenarios.empty());

    // Run smelt() on the first scenario and verify it works.
    auto scenario = scenarios[0];
    EXPECT_EQ(scenario->scenarioName(), "DummyScenario");
    scenario->smelt();

    // Since our dummy scenario sets a flag when smelt() is called, verify that.
    DummyScenario* dummyScenario = dynamic_cast<DummyScenario*>(scenario.get());
    ASSERT_NE(dummyScenario, nullptr);
    EXPECT_TRUE(dummyScenario->wasSmelted());

    // Log success
    ForgeLog::info("DummyScenario successfully created and executed.");
}