#include <gtest/gtest.h>
#include <iostream>

// Step Interface
class cppforge_agent_reports_installed_packages_steps {
public:
    virtual void given_an_agent_is_registered() {
        FAIL() << "[STEP NOT IMPLEMENTED] Given an agent is registered";
    }
    virtual void when_the_master_requests_a_package_inventory() {
        FAIL() << "[STEP NOT IMPLEMENTED] When the master requests a package inventory";
    }
    virtual void then_the_agent_returns_a_list_of_installed_packages() {
        FAIL() << "[STEP NOT IMPLEMENTED] Then the agent returns a list of installed packages";
    }

    virtual ~cppforge_agent_reports_installed_packages_steps() = default;
};

// Stub Implementation (throws failures)
class stub_agent_reports_installed_packages_steps : public cppforge_agent_reports_installed_packages_steps {
    // No overrides – just uses FAIL() behavior from base class
};

// Test Case
TEST(cppforge_agent_reports_installed_packages_test, executes_scenario) {
    stub_agent_reports_installed_packages_steps steps;

    std::cout << "[GIVEN] Given an agent is registered" << std::endl;
    steps.given_an_agent_is_registered();
    std::cout << "[WHEN] When the master requests a package inventory" << std::endl;
    steps.when_the_master_requests_a_package_inventory();
    std::cout << "[THEN] Then the agent returns a list of installed packages" << std::endl;
    steps.then_the_agent_returns_a_list_of_installed_packages();
}