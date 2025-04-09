#include <gtest/gtest.h>
#include <iostream>
#include <memory>

// Step Interface
class scn_4_remote_command_execution_execute_shell_command_on_target_node {
public:
    virtual void given_the_master_sends_a_command_ls_la_to_the_agent() {
        FAIL() << "[STEP NOT IMPLEMENTED] Given the master sends a command \"ls -la\" to the agent";
    }
    virtual void when_the_agent_receives_the_request() {
        FAIL() << "[STEP NOT IMPLEMENTED] When the agent receives the request";
    }
    virtual void then_it_should_execute_the_command_in_a_secure_subprocess() {
        FAIL() << "[STEP NOT IMPLEMENTED] Then it should execute the command in a secure subprocess";
    }
    virtual void and_it_should_capture_stdout_and_stderr() {
        FAIL() << "[STEP NOT IMPLEMENTED] And it should capture stdout and stderr";
    }

    virtual ~scn_4_remote_command_execution_execute_shell_command_on_target_node() = default;
};

// Stub Implementation (throws failures)
class stub_scn_4_remote_command_execution_execute_shell_command_on_target_node : public scn_4_remote_command_execution_execute_shell_command_on_target_node {
    // No overrides – just uses FAIL() behavior from base class
};

#ifdef HAS_IMPL_scn_4_remote_command_execution_execute_shell_command_on_target_node
static std::unique_ptr<scn_4_remote_command_execution_execute_shell_command_on_target_node> forge_bdd_steps() {
    return std::make_unique<impl_scn_4_remote_command_execution_execute_shell_command_on_target_node>();
}
#else
static std::unique_ptr<scn_4_remote_command_execution_execute_shell_command_on_target_node> forge_bdd_steps() {
    return std::make_unique<stub_scn_4_remote_command_execution_execute_shell_command_on_target_node>();
}
#endif

// Test Case
TEST(scn_4_remote_command_execution_execute_shell_command_on_target_node_test, executes_scenario) {
    auto steps = forge_bdd_steps();

    std::cout << "[GIVEN] Given the master sends a command \"ls -la\" to the agent" << std::endl;
    steps->given_the_master_sends_a_command_ls_la_to_the_agent();
    std::cout << "[WHEN] When the agent receives the request" << std::endl;
    steps->when_the_agent_receives_the_request();
    std::cout << "[THEN] Then it should execute the command in a secure subprocess" << std::endl;
    steps->then_it_should_execute_the_command_in_a_secure_subprocess();
    std::cout << "[AND] And it should capture stdout and stderr" << std::endl;
    steps->and_it_should_capture_stdout_and_stderr();
}
