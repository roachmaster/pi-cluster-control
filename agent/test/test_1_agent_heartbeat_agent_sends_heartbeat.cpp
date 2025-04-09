#include <gtest/gtest.h>
#include <iostream>
#include <memory>

// Step Interface
class scn_1_agent_heartbeat_agent_sends_heartbeat {
public:
    virtual void given_the_agent_is_running() {
        FAIL() << "[STEP NOT IMPLEMENTED] Given the agent is running";
    }
    virtual void when_5_seconds_pass() {
        FAIL() << "[STEP NOT IMPLEMENTED] When 5 seconds pass";
    }
    virtual void then_it_should_publish_a_heartbeat_signal_to_the_master() {
        FAIL() << "[STEP NOT IMPLEMENTED] Then it should publish a heartbeat signal to the master";
    }

    virtual ~scn_1_agent_heartbeat_agent_sends_heartbeat() = default;
};

// Stub Implementation (throws failures)
class stub_scn_1_agent_heartbeat_agent_sends_heartbeat : public scn_1_agent_heartbeat_agent_sends_heartbeat {
    // No overrides – just uses FAIL() behavior from base class
};

#ifdef HAS_IMPL_scn_1_agent_heartbeat_agent_sends_heartbeat
static std::unique_ptr<scn_1_agent_heartbeat_agent_sends_heartbeat> forge_bdd_steps() {
    return std::make_unique<impl_scn_1_agent_heartbeat_agent_sends_heartbeat>();
}
#else
static std::unique_ptr<scn_1_agent_heartbeat_agent_sends_heartbeat> forge_bdd_steps() {
    return std::make_unique<stub_scn_1_agent_heartbeat_agent_sends_heartbeat>();
}
#endif

// Test Case
TEST(scn_1_agent_heartbeat_agent_sends_heartbeat_test, executes_scenario) {
    auto steps = forge_bdd_steps();

    std::cout << "[GIVEN] Given the agent is running" << std::endl;
    steps->given_the_agent_is_running();
    std::cout << "[WHEN] When 5 seconds pass" << std::endl;
    steps->when_5_seconds_pass();
    std::cout << "[THEN] Then it should publish a heartbeat signal to the master" << std::endl;
    steps->then_it_should_publish_a_heartbeat_signal_to_the_master();
}
