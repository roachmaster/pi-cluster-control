#include <gtest/gtest.h>
#include <iostream>
#include <memory>

// Step Interface
class scn_1_schema_definition_and_validation_across_config_files_empty_file_scenario {
public:
    virtual void given_an_empty_yaml_configuration_file_config_example_yaml() {
        FAIL() << "[STEP NOT IMPLEMENTED] Given an empty YAML configuration file \"config/example.yaml\"";
    }
    virtual void when_the_file_is_loaded_into_the_system() {
        FAIL() << "[STEP NOT IMPLEMENTED] When the file is loaded into the system";
    }
    virtual void then_an_error_is_returned_indicating_that_the_file_is_empty_or_a_default_configuration_is_generated() {
        FAIL() << "[STEP NOT IMPLEMENTED] Then an error is returned indicating that the file is empty or a default configuration is generated";
    }

    virtual ~scn_1_schema_definition_and_validation_across_config_files_empty_file_scenario() = default;
};

// Stub Implementation (throws failures)
class stub_scn_1_schema_definition_and_validation_across_config_files_empty_file_scenario : public scn_1_schema_definition_and_validation_across_config_files_empty_file_scenario {
    // No overrides – just uses FAIL() behavior from base class
};

#ifdef HAS_IMPL_scn_1_schema_definition_and_validation_across_config_files_empty_file_scenario
static std::unique_ptr<scn_1_schema_definition_and_validation_across_config_files_empty_file_scenario> forge_bdd_steps() {
    return std::make_unique<impl_scn_1_schema_definition_and_validation_across_config_files_empty_file_scenario>();
}
#else
static std::unique_ptr<scn_1_schema_definition_and_validation_across_config_files_empty_file_scenario> forge_bdd_steps() {
    return std::make_unique<stub_scn_1_schema_definition_and_validation_across_config_files_empty_file_scenario>();
}
#endif

// Test Case
TEST(scn_1_schema_definition_and_validation_across_config_files_empty_file_scenario_test, executes_scenario) {
    auto steps = forge_bdd_steps();

    std::cout << "[GIVEN] Given an empty YAML configuration file \"config/example.yaml\"" << std::endl;
    steps->given_an_empty_yaml_configuration_file_config_example_yaml();
    std::cout << "[WHEN] When the file is loaded into the system" << std::endl;
    steps->when_the_file_is_loaded_into_the_system();
    std::cout << "[THEN] Then an error is returned indicating that the file is empty or a default configuration is generated" << std::endl;
    steps->then_an_error_is_returned_indicating_that_the_file_is_empty_or_a_default_configuration_is_generated();
}
