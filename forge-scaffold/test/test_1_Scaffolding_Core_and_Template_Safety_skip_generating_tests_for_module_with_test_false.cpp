#include <gtest/gtest.h>
#include <iostream>
#include <memory>

// Step Interface
class scn_1_scaffolding_core_and_template_safety_skip_generating_tests_for_module_with_test_false {
public:
    virtual void given_the_module_logging_has_test_disabled() {
        FAIL() << "[STEP NOT IMPLEMENTED] Given the module \"logging\" has test disabled";
    }
    virtual void when_i_run_the_cppforge_scaffolding_tool() {
        FAIL() << "[STEP NOT IMPLEMENTED] When I run the cppforge scaffolding tool";
    }
    virtual void then_no_test_directory_should_be_created_for_the_logging_module() {
        FAIL() << "[STEP NOT IMPLEMENTED] Then no \"test\" directory should be created for the \"logging\" module";
    }

    virtual ~scn_1_scaffolding_core_and_template_safety_skip_generating_tests_for_module_with_test_false() = default;
};

// Stub Implementation (throws failures)
class stub_scn_1_scaffolding_core_and_template_safety_skip_generating_tests_for_module_with_test_false : public scn_1_scaffolding_core_and_template_safety_skip_generating_tests_for_module_with_test_false {
    // No overrides – just uses FAIL() behavior from base class
};

#ifdef HAS_IMPL_scn_1_scaffolding_core_and_template_safety_skip_generating_tests_for_module_with_test_false
static std::unique_ptr<scn_1_scaffolding_core_and_template_safety_skip_generating_tests_for_module_with_test_false> forge_bdd_steps() {
    return std::make_unique<impl_scn_1_scaffolding_core_and_template_safety_skip_generating_tests_for_module_with_test_false>();
}
#else
static std::unique_ptr<scn_1_scaffolding_core_and_template_safety_skip_generating_tests_for_module_with_test_false> forge_bdd_steps() {
    return std::make_unique<stub_scn_1_scaffolding_core_and_template_safety_skip_generating_tests_for_module_with_test_false>();
}
#endif

// Test Case
TEST(scn_1_scaffolding_core_and_template_safety_skip_generating_tests_for_module_with_test_false_test, executes_scenario) {
    auto steps = forge_bdd_steps();

    std::cout << "[GIVEN] Given the module \"logging\" has test disabled" << std::endl;
    steps->given_the_module_logging_has_test_disabled();
    std::cout << "[WHEN] When I run the cppforge scaffolding tool" << std::endl;
    steps->when_i_run_the_cppforge_scaffolding_tool();
    std::cout << "[THEN] Then no \"test\" directory should be created for the \"logging\" module" << std::endl;
    steps->then_no_test_directory_should_be_created_for_the_logging_module();
}
