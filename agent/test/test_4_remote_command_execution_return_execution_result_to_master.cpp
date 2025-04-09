#include <gtest/gtest.h>
#include <iostream>
#include <memory>

// Step Interface
class scn_4_remote_command_execution_return_execution_result_to_master {
public:
    virtual void given_the_command_has_been_executed() {
        FAIL() << "[STEP NOT IMPLEMENTED] Given the command has been executed";
    }
    virtual void when_the_output_is_available() {
        FAIL() << "[STEP NOT IMPLEMENTED] When the output is available";
    }
    virtual void then_the_agent_should_send_the_result_and_exit_code_back_to_the_master() {
        FAIL() << "[STEP NOT IMPLEMENTED] Then the agent should send the result and exit code back to the master";
    }

    virtual ~scn_4_remote_command_execution_return_execution_result_to_master() = default;
};

// Stub Implementation (throws failures)
class stub_scn_4_remote_command_execution_return_execution_result_to_master : public scn_4_remote_command_execution_return_execution_result_to_master {
    // No overrides – just uses FAIL() behavior from base class
};

#ifdef HAS_IMPL_scn_4_remote_command_execution_return_execution_result_to_master
static std::unique_ptr<scn_4_remote_command_execution_return_execution_result_to_master> forge_bdd_steps() {
    return std::make_unique<impl_scn_4_remote_command_execution_return_execution_result_to_master>();
}
#else
static std::unique_ptr<scn_4_remote_command_execution_return_execution_result_to_master> forge_bdd_steps() {
    return std::make_unique<stub_scn_4_remote_command_execution_return_execution_result_to_master>();
}
#endif

// Test Case
TEST(scn_4_remote_command_execution_return_execution_result_to_master_test, executes_scenario) {
    auto steps = forge_bdd_steps();

    std::cout << "[GIVEN] Given the command has been executed" << std::endl;
    steps->given_the_command_has_been_executed();
    std::cout << "[WHEN] When the output is available" << std::endl;
    steps->when_the_output_is_available();
    std::cout << "[THEN] Then the agent should send the result and exit code back to the master" << std::endl;
    steps->then_the_agent_should_send_the_result_and_exit_code_back_to_the_master();
}
