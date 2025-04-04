#include <gtest/gtest.h>
#include <iostream>

// Step Interface
class cppforge_agent_misses_heartbeat_steps {
public:
    virtual void given_a_registered_agent_was_previously_active() {
        FAIL() << "[STEP NOT IMPLEMENTED] Given a registered agent was previously active";
    }
    virtual void when_no_heartbeat_is_received_within_the_timeout_window() {
        FAIL() << "[STEP NOT IMPLEMENTED] When no heartbeat is received within the timeout window";
    }
    virtual void then_the_master_marks_the_agent_as_inactive() {
        FAIL() << "[STEP NOT IMPLEMENTED] Then the master marks the agent as inactive";
    }

    virtual ~cppforge_agent_misses_heartbeat_steps() = default;
};

// Stub Implementation (throws failures)
class stub_agent_misses_heartbeat_steps : public cppforge_agent_misses_heartbeat_steps {
    // No overrides – just uses FAIL() behavior from base class
};

// Test Case
TEST(cppforge_agent_misses_heartbeat_test, executes_scenario) {
    stub_agent_misses_heartbeat_steps steps;

    std::cout << "[GIVEN] Given a registered agent was previously active" << std::endl;
    steps.given_a_registered_agent_was_previously_active();
    std::cout << "[WHEN] When no heartbeat is received within the timeout window" << std::endl;
    steps.when_no_heartbeat_is_received_within_the_timeout_window();
    std::cout << "[THEN] Then the master marks the agent as inactive" << std::endl;
    steps.then_the_master_marks_the_agent_as_inactive();
}