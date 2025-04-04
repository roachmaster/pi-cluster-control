#include <gtest/gtest.h>
#include <iostream>

// Step Interface
class cppforge_skip_generating_tests_for_module_with_test_false_steps {
public:
    virtual void given_the_module_logging_has_test_disabled() {
        FAIL() << "[STEP NOT IMPLEMENTED] Given the module "logging" has test disabled";
    }
    virtual void when_i_run_the_cppforge_scaffolding_tool() {
        FAIL() << "[STEP NOT IMPLEMENTED] When I run the cppforge scaffolding tool";
    }
    virtual void then_no_test_directory_should_be_created_for_the_logging_module() {
        FAIL() << "[STEP NOT IMPLEMENTED] Then no "test" directory should be created for the "logging" module";
    }

    virtual ~cppforge_skip_generating_tests_for_module_with_test_false_steps() = default;
};

// Stub Implementation (throws failures)
class stub_skip_generating_tests_for_module_with_test_false_steps : public cppforge_skip_generating_tests_for_module_with_test_false_steps {
    // No overrides – just uses FAIL() behavior from base class
};

// Test Case
TEST(cppforge_skip_generating_tests_for_module_with_test_false_test, executes_scenario) {
    stub_skip_generating_tests_for_module_with_test_false_steps steps;

    std::cout << "[GIVEN] Given the module "logging" has test disabled" << std::endl;
    steps.given_the_module_logging_has_test_disabled();
    std::cout << "[WHEN] When I run the cppforge scaffolding tool" << std::endl;
    steps.when_i_run_the_cppforge_scaffolding_tool();
    std::cout << "[THEN] Then no "test" directory should be created for the "logging" module" << std::endl;
    steps.then_no_test_directory_should_be_created_for_the_logging_module();
}