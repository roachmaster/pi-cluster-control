#include <gtest/gtest.h>
#include <iostream>
#include <memory>

// Step Interface
class scn_1_scaffolding_core_and_template_safety_generate_a_new_executable_module {
public:
    virtual void given_a_module_name_monitor() {
        FAIL() << "[STEP NOT IMPLEMENTED] Given a module name \"monitor\"";
    }
    virtual void and_the_module_type_is_exe() {
        FAIL() << "[STEP NOT IMPLEMENTED] And the module type is \"exe\"";
    }
    virtual void when_i_run_the_cppforge_scaffolding_tool() {
        FAIL() << "[STEP NOT IMPLEMENTED] When I run the cppforge scaffolding tool";
    }
    virtual void then_a_directory_named_monitor_should_be_created() {
        FAIL() << "[STEP NOT IMPLEMENTED] Then a directory named \"monitor\" should be created";
    }
    virtual void and_it_should_contain_cmakelists_txt() {
        FAIL() << "[STEP NOT IMPLEMENTED] And it should contain \"CMakeLists.txt\"";
    }
    virtual void and_it_should_contain_src_main_cpp() {
        FAIL() << "[STEP NOT IMPLEMENTED] And it should contain \"src/main.cpp\"";
    }
    virtual void and_it_should_contain_an_include_directory() {
        FAIL() << "[STEP NOT IMPLEMENTED] And it should contain an \"include/\" directory";
    }

    virtual ~scn_1_scaffolding_core_and_template_safety_generate_a_new_executable_module() = default;
};

// Stub Implementation (throws failures)
class stub_scn_1_scaffolding_core_and_template_safety_generate_a_new_executable_module : public scn_1_scaffolding_core_and_template_safety_generate_a_new_executable_module {
    // No overrides – just uses FAIL() behavior from base class
};

#ifdef HAS_IMPL_scn_1_scaffolding_core_and_template_safety_generate_a_new_executable_module
static std::unique_ptr<scn_1_scaffolding_core_and_template_safety_generate_a_new_executable_module> forge_bdd_steps() {
    return std::make_unique<impl_scn_1_scaffolding_core_and_template_safety_generate_a_new_executable_module>();
}
#else
static std::unique_ptr<scn_1_scaffolding_core_and_template_safety_generate_a_new_executable_module> forge_bdd_steps() {
    return std::make_unique<stub_scn_1_scaffolding_core_and_template_safety_generate_a_new_executable_module>();
}
#endif

// Test Case
TEST(scn_1_scaffolding_core_and_template_safety_generate_a_new_executable_module_test, executes_scenario) {
    auto steps = forge_bdd_steps();

    std::cout << "[GIVEN] Given a module name \"monitor\"" << std::endl;
    steps->given_a_module_name_monitor();
    std::cout << "[AND] And the module type is \"exe\"" << std::endl;
    steps->and_the_module_type_is_exe();
    std::cout << "[WHEN] When I run the cppforge scaffolding tool" << std::endl;
    steps->when_i_run_the_cppforge_scaffolding_tool();
    std::cout << "[THEN] Then a directory named \"monitor\" should be created" << std::endl;
    steps->then_a_directory_named_monitor_should_be_created();
    std::cout << "[AND] And it should contain \"CMakeLists.txt\"" << std::endl;
    steps->and_it_should_contain_cmakelists_txt();
    std::cout << "[AND] And it should contain \"src/main.cpp\"" << std::endl;
    steps->and_it_should_contain_src_main_cpp();
    std::cout << "[AND] And it should contain an \"include/\" directory" << std::endl;
    steps->and_it_should_contain_an_include_directory();
}
