#include <gtest/gtest.h>
#include <iostream>

// Step Interface
class cppforge_agent_lists_all_packages_steps {
public:
    virtual void given_the_agent_is_running() {
        FAIL() << "[STEP NOT IMPLEMENTED] Given the agent is running";
    }
    virtual void when_it_scans_for_installed_packages() {
        FAIL() << "[STEP NOT IMPLEMENTED] When it scans for installed packages";
    }
    virtual void then_it_should_return_a_full_list_of_all_installed_packages() {
        FAIL() << "[STEP NOT IMPLEMENTED] Then it should return a full list of all installed packages";
    }

    virtual ~cppforge_agent_lists_all_packages_steps() = default;
};

// Stub Implementation (throws failures)
class stub_agent_lists_all_packages_steps : public cppforge_agent_lists_all_packages_steps {
    // No overrides – just uses FAIL() behavior from base class
};

// BDD Scenario Test
TEST(cppforge_agent_lists_all_packages_test, ExecutesFullScenario) {
    stub_agent_lists_all_packages_steps steps;

    std::cout << "\n=== Running BDD Scenario: cppforge_agent_lists_all_packages_test ===" << std::endl;
    std::cout << "[GIVEN] Given the agent is running" << std::endl;
    steps.given_the_agent_is_running();
    std::cout << "[WHEN] When it scans for installed packages" << std::endl;
    steps.when_it_scans_for_installed_packages();
    std::cout << "[THEN] Then it should return a full list of all installed packages" << std::endl;
    steps.then_it_should_return_a_full_list_of_all_installed_packages();
}
