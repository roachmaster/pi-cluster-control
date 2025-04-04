#include <gtest/gtest.h>
#include <iostream>

// Step Interface
class cppforge_do_not_generate_test_directory_for_non_exe_lib_modules_steps {
public:
    virtual void given_a_module_type_react() {
        FAIL() << "[STEP NOT IMPLEMENTED] Given a module type "react"";
    }
    virtual void when_i_run_the_scaffolding_tool() {
        FAIL() << "[STEP NOT IMPLEMENTED] When I run the scaffolding tool";
    }
    virtual void then_the_module_should_not_have_a_test_directory() {
        FAIL() << "[STEP NOT IMPLEMENTED] Then the module should not have a test directory";
    }

    virtual ~cppforge_do_not_generate_test_directory_for_non_exe_lib_modules_steps() = default;
};

// Stub Implementation (throws failures)
class stub_do_not_generate_test_directory_for_non_exe_lib_modules_steps : public cppforge_do_not_generate_test_directory_for_non_exe_lib_modules_steps {
    // No overrides – just uses FAIL() behavior from base class
};

// BDD Scenario Test
TEST(cppforge_do_not_generate_test_directory_for_non_exe_lib_modules_test, ExecutesFullScenario) {
    stub_do_not_generate_test_directory_for_non_exe_lib_modules_steps steps;

    std::cout << "\n=== Running BDD Scenario: cppforge_do_not_generate_test_directory_for_non_exe_lib_modules_test ===" << std::endl;
    std::cout << "[GIVEN] Given a module type "react"" << std::endl;
    steps.given_a_module_type_react();
    std::cout << "[WHEN] When I run the scaffolding tool" << std::endl;
    steps.when_i_run_the_scaffolding_tool();
    std::cout << "[THEN] Then the module should not have a test directory" << std::endl;
    steps.then_the_module_should_not_have_a_test_directory();
}
