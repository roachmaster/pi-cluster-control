#include <gtest/gtest.h>
#include <iostream>
#include <memory>

// Step Interface
class scn_1_schema_definition_and_validation_across_config_files_schema_validation_failure_due_to_invalid_values {
public:
    virtual void given_a_yaml_configuration_file_config_example_yaml_that_contains_invalid_values_for_required_keys() {
        FAIL() << "[STEP NOT IMPLEMENTED] Given a YAML configuration file \"config/example.yaml\" that contains invalid values for required keys";
    }
    virtual void when_the_file_is_loaded_into_the_system() {
        FAIL() << "[STEP NOT IMPLEMENTED] When the file is loaded into the system";
    }
    virtual void then_an_error_is_returned_indicating_that_some_values_are_invalid() {
        FAIL() << "[STEP NOT IMPLEMENTED] Then an error is returned indicating that some values are invalid";
    }

    virtual ~scn_1_schema_definition_and_validation_across_config_files_schema_validation_failure_due_to_invalid_values() = default;
};

// Stub Implementation (throws failures)
class stub_scn_1_schema_definition_and_validation_across_config_files_schema_validation_failure_due_to_invalid_values : public scn_1_schema_definition_and_validation_across_config_files_schema_validation_failure_due_to_invalid_values {
    // No overrides – just uses FAIL() behavior from base class
};

#ifdef HAS_IMPL_scn_1_schema_definition_and_validation_across_config_files_schema_validation_failure_due_to_invalid_values
static std::unique_ptr<scn_1_schema_definition_and_validation_across_config_files_schema_validation_failure_due_to_invalid_values> forge_bdd_steps() {
    return std::make_unique<impl_scn_1_schema_definition_and_validation_across_config_files_schema_validation_failure_due_to_invalid_values>();
}
#else
static std::unique_ptr<scn_1_schema_definition_and_validation_across_config_files_schema_validation_failure_due_to_invalid_values> forge_bdd_steps() {
    return std::make_unique<stub_scn_1_schema_definition_and_validation_across_config_files_schema_validation_failure_due_to_invalid_values>();
}
#endif

// Test Case
TEST(scn_1_schema_definition_and_validation_across_config_files_schema_validation_failure_due_to_invalid_values_test, executes_scenario) {
    auto steps = forge_bdd_steps();

    std::cout << "[GIVEN] Given a YAML configuration file \"config/example.yaml\" that contains invalid values for required keys" << std::endl;
    steps->given_a_yaml_configuration_file_config_example_yaml_that_contains_invalid_values_for_required_keys();
    std::cout << "[WHEN] When the file is loaded into the system" << std::endl;
    steps->when_the_file_is_loaded_into_the_system();
    std::cout << "[THEN] Then an error is returned indicating that some values are invalid" << std::endl;
    steps->then_an_error_is_returned_indicating_that_some_values_are_invalid();
}
