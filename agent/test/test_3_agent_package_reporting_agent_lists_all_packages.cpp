#include <gtest/gtest.h>
#include <iostream>

// Step Interface
class scn_3_agent_package_reporting_agent_lists_all_packages {
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

    virtual ~scn_3_agent_package_reporting_agent_lists_all_packages() = default;
};

// Stub Implementation (throws failures)
class stub_scn_3_agent_package_reporting_agent_lists_all_packages : public scn_3_agent_package_reporting_agent_lists_all_packages {
    // No overrides – just uses FAIL() behavior from base class
};

// Test Case
TEST(scn_3_agent_package_reporting_agent_lists_all_packages_test, executes_scenario) {
    stub_scn_3_agent_package_reporting_agent_lists_all_packages steps;

    std::cout << "[GIVEN] Given the agent is running" << std::endl;
    steps.given_the_agent_is_running();
    std::cout << "[WHEN] When it scans for installed packages" << std::endl;
    steps.when_it_scans_for_installed_packages();
    std::cout << "[THEN] Then it should return a full list of all installed packages" << std::endl;
    steps.then_it_should_return_a_full_list_of_all_installed_packages();
}
