#include <gtest/gtest.h>
#include <iostream>
#include <memory>

// Step Interface
class scn_1_monitor_and_register_agents_agent_misses_heartbeat {
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

    virtual ~scn_1_monitor_and_register_agents_agent_misses_heartbeat() = default;
};

// Stub Implementation (throws failures)
class stub_scn_1_monitor_and_register_agents_agent_misses_heartbeat : public scn_1_monitor_and_register_agents_agent_misses_heartbeat {
    // No overrides – just uses FAIL() behavior from base class
};

#ifdef HAS_IMPL_scn_1_monitor_and_register_agents_agent_misses_heartbeat
static std::unique_ptr<scn_1_monitor_and_register_agents_agent_misses_heartbeat> forge_bdd_steps() {
    return std::make_unique<impl_scn_1_monitor_and_register_agents_agent_misses_heartbeat>();
}
#else
static std::unique_ptr<scn_1_monitor_and_register_agents_agent_misses_heartbeat> forge_bdd_steps() {
    return std::make_unique<stub_scn_1_monitor_and_register_agents_agent_misses_heartbeat>();
}
#endif

// Test Case
TEST(scn_1_monitor_and_register_agents_agent_misses_heartbeat_test, executes_scenario) {
    auto steps = forge_bdd_steps();

    std::cout << "[GIVEN] Given a registered agent was previously active" << std::endl;
    steps->given_a_registered_agent_was_previously_active();
    std::cout << "[WHEN] When no heartbeat is received within the timeout window" << std::endl;
    steps->when_no_heartbeat_is_received_within_the_timeout_window();
    std::cout << "[THEN] Then the master marks the agent as inactive" << std::endl;
    steps->then_the_master_marks_the_agent_as_inactive();
}
