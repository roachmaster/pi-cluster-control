#include <gtest/gtest.h>
#include <iostream>

// Step Interface
class cppforge_docker_is_active_steps {
public:
    virtual void given_docker_is_installed() {
        FAIL() << "[STEP NOT IMPLEMENTED] Given Docker is installed";
    }
    virtual void when_the_agent_checks_for_running_services() {
        FAIL() << "[STEP NOT IMPLEMENTED] When the agent checks for running services";
    }
    virtual void then_docker_should_be_reported_as_running() {
        FAIL() << "[STEP NOT IMPLEMENTED] Then Docker should be reported as running";
    }

    virtual ~cppforge_docker_is_active_steps() = default;
};

// Stub Implementation (throws failures)
class stub_docker_is_active_steps : public cppforge_docker_is_active_steps {
    // No overrides – just uses FAIL() behavior from base class
};

// BDD Scenario Test
TEST(cppforge_docker_is_active_test, ExecutesFullScenario) {
    stub_docker_is_active_steps steps;

    std::cout << "\n=== Running BDD Scenario: cppforge_docker_is_active_test ===" << std::endl;
    std::cout << "[GIVEN] Given Docker is installed" << std::endl;
    steps.given_docker_is_installed();
    std::cout << "[WHEN] When the agent checks for running services" << std::endl;
    steps.when_the_agent_checks_for_running_services();
    std::cout << "[THEN] Then Docker should be reported as running" << std::endl;
    steps.then_docker_should_be_reported_as_running();
}
