#include <gtest/gtest.h>
#include <iostream>

// Step Interface
class cppforge_generate_a_new_library_module_steps {
public:
    virtual void given_a_module_name_utils() {
        FAIL() << "[STEP NOT IMPLEMENTED] Given a module name "utils"";
    }
    virtual void and_the_module_type_is_lib() {
        FAIL() << "[STEP NOT IMPLEMENTED] And the module type is "lib"";
    }
    virtual void when_i_run_the_cppforge_scaffolding_tool() {
        FAIL() << "[STEP NOT IMPLEMENTED] When I run the cppforge scaffolding tool";
    }
    virtual void then_a_directory_named_utils_should_be_created() {
        FAIL() << "[STEP NOT IMPLEMENTED] Then a directory named "utils" should be created";
    }
    virtual void and_it_should_contain_cmakelists_txt() {
        FAIL() << "[STEP NOT IMPLEMENTED] And it should contain "CMakeLists.txt"";
    }
    virtual void and_it_should_contain_src_utils_cpp() {
        FAIL() << "[STEP NOT IMPLEMENTED] And it should contain "src/utils.cpp"";
    }
    virtual void and_it_should_contain_include_utils_hpp() {
        FAIL() << "[STEP NOT IMPLEMENTED] And it should contain "include/utils.hpp"";
    }

    virtual ~cppforge_generate_a_new_library_module_steps() = default;
};

// Stub Implementation (throws failures)
class stub_generate_a_new_library_module_steps : public cppforge_generate_a_new_library_module_steps {
    // No overrides – just uses FAIL() behavior from base class
};

// BDD Scenario Test
TEST(cppforge_generate_a_new_library_module_test, ExecutesFullScenario) {
    stub_generate_a_new_library_module_steps steps;

    std::cout << "\n=== Running BDD Scenario: cppforge_generate_a_new_library_module_test ===" << std::endl;
    std::cout << "[GIVEN] Given a module name "utils"" << std::endl;
    steps.given_a_module_name_utils();
    std::cout << "[AND] And the module type is "lib"" << std::endl;
    steps.and_the_module_type_is_lib();
    std::cout << "[WHEN] When I run the cppforge scaffolding tool" << std::endl;
    steps.when_i_run_the_cppforge_scaffolding_tool();
    std::cout << "[THEN] Then a directory named "utils" should be created" << std::endl;
    steps.then_a_directory_named_utils_should_be_created();
    std::cout << "[AND] And it should contain "CMakeLists.txt"" << std::endl;
    steps.and_it_should_contain_cmakelists_txt();
    std::cout << "[AND] And it should contain "src/utils.cpp"" << std::endl;
    steps.and_it_should_contain_src_utils_cpp();
    std::cout << "[AND] And it should contain "include/utils.hpp"" << std::endl;
    steps.and_it_should_contain_include_utils_hpp();
}
