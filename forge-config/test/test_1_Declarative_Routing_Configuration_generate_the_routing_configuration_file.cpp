#include <gtest/gtest.h>
#include <iostream>
#include <memory>

// Step Interface
class scn_1_declarative_routing_configuration_generate_the_routing_configuration_file {
public:
    virtual void given_the_config_cppforge_yaml_file_does_not_exist() {
        FAIL() << "[STEP NOT IMPLEMENTED] Given the config/cppforge.yaml file does not exist";
    }
    virtual void when_i_run_the_routing_setup_tool() {
        FAIL() << "[STEP NOT IMPLEMENTED] When I run the routing setup tool";
    }
    virtual void then_a_file_named_cppforge_yaml_should_be_created_in_the_config_directory() {
        FAIL() << "[STEP NOT IMPLEMENTED] Then a file named \"cppforge.yaml\" should be created in the config directory";
    }

    virtual ~scn_1_declarative_routing_configuration_generate_the_routing_configuration_file() = default;
};

// Stub Implementation (throws failures)
class stub_scn_1_declarative_routing_configuration_generate_the_routing_configuration_file : public scn_1_declarative_routing_configuration_generate_the_routing_configuration_file {
    // No overrides – just uses FAIL() behavior from base class
};

#ifdef HAS_IMPL_scn_1_declarative_routing_configuration_generate_the_routing_configuration_file
static std::unique_ptr<scn_1_declarative_routing_configuration_generate_the_routing_configuration_file> forge_bdd_steps() {
    return std::make_unique<impl_scn_1_declarative_routing_configuration_generate_the_routing_configuration_file>();
}
#else
static std::unique_ptr<scn_1_declarative_routing_configuration_generate_the_routing_configuration_file> forge_bdd_steps() {
    return std::make_unique<stub_scn_1_declarative_routing_configuration_generate_the_routing_configuration_file>();
}
#endif

// Test Case
TEST(scn_1_declarative_routing_configuration_generate_the_routing_configuration_file_test, executes_scenario) {
    auto steps = forge_bdd_steps();

    std::cout << "[GIVEN] Given the config/cppforge.yaml file does not exist" << std::endl;
    steps->given_the_config_cppforge_yaml_file_does_not_exist();
    std::cout << "[WHEN] When I run the routing setup tool" << std::endl;
    steps->when_i_run_the_routing_setup_tool();
    std::cout << "[THEN] Then a file named \"cppforge.yaml\" should be created in the config directory" << std::endl;
    steps->then_a_file_named_cppforge_yaml_should_be_created_in_the_config_directory();
}
