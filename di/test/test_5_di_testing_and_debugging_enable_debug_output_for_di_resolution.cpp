#include <gtest/gtest.h>
#include <iostream>

// Step Interface
class scn_5_di_testing_and_debugging_enable_debug_output_for_di_resolution {
public:
    virtual void given_the_di_container_is_in_debug_mode() {
        FAIL() << "[STEP NOT IMPLEMENTED] Given the DI container is in debug mode";
    }
    virtual void when_resolving_a_class() {
        FAIL() << "[STEP NOT IMPLEMENTED] When resolving a class";
    }
    virtual void then_it_should_print_which_concrete_implementation_was_used() {
        FAIL() << "[STEP NOT IMPLEMENTED] Then it should print which concrete implementation was used";
    }

    virtual ~scn_5_di_testing_and_debugging_enable_debug_output_for_di_resolution() = default;
};

// Stub Implementation (throws failures)
class stub_scn_5_di_testing_and_debugging_enable_debug_output_for_di_resolution : public scn_5_di_testing_and_debugging_enable_debug_output_for_di_resolution {
    // No overrides – just uses FAIL() behavior from base class
};

// Test Case
TEST(scn_5_di_testing_and_debugging_enable_debug_output_for_di_resolution_test, executes_scenario) {
    stub_scn_5_di_testing_and_debugging_enable_debug_output_for_di_resolution steps;

    std::cout << "[GIVEN] Given the DI container is in debug mode" << std::endl;
    steps.given_the_di_container_is_in_debug_mode();
    std::cout << "[WHEN] When resolving a class" << std::endl;
    steps.when_resolving_a_class();
    std::cout << "[THEN] Then it should print which concrete implementation was used" << std::endl;
    steps.then_it_should_print_which_concrete_implementation_was_used();
}
