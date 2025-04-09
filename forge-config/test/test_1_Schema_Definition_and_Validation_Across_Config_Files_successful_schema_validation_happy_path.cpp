#include <gtest/gtest.h>
#include <iostream>
#include <memory>

// Step Interface
class scn_1_schema_definition_and_validation_across_config_files_successful_schema_validation_happy_path {
public:
    virtual void given_a_well_formed_yaml_configuration_file_config_example_yaml_that_conforms_to_the_schema_and_has_some_optional_keys_missing() {
        FAIL() << "[STEP NOT IMPLEMENTED] Given a well-formed YAML configuration file \"config/example.yaml\" that conforms to the schema and has some optional keys missing";
    }
    virtual void when_the_file_is_loaded_into_the_system() {
        FAIL() << "[STEP NOT IMPLEMENTED] When the file is loaded into the system";
    }
    virtual void then_the_contents_are_validated_against_the_predefined_schema_and_default_values_are_applied_with_no_errors_reported() {
        FAIL() << "[STEP NOT IMPLEMENTED] Then the contents are validated against the predefined schema and default values are applied with no errors reported";
    }

    virtual ~scn_1_schema_definition_and_validation_across_config_files_successful_schema_validation_happy_path() = default;
};

// Stub Implementation (throws failures)
class stub_scn_1_schema_definition_and_validation_across_config_files_successful_schema_validation_happy_path : public scn_1_schema_definition_and_validation_across_config_files_successful_schema_validation_happy_path {
    // No overrides – just uses FAIL() behavior from base class
};

#ifdef HAS_IMPL_scn_1_schema_definition_and_validation_across_config_files_successful_schema_validation_happy_path
static std::unique_ptr<scn_1_schema_definition_and_validation_across_config_files_successful_schema_validation_happy_path> forge_bdd_steps() {
    return std::make_unique<impl_scn_1_schema_definition_and_validation_across_config_files_successful_schema_validation_happy_path>();
}
#else
static std::unique_ptr<scn_1_schema_definition_and_validation_across_config_files_successful_schema_validation_happy_path> forge_bdd_steps() {
    return std::make_unique<stub_scn_1_schema_definition_and_validation_across_config_files_successful_schema_validation_happy_path>();
}
#endif

// Test Case
TEST(scn_1_schema_definition_and_validation_across_config_files_successful_schema_validation_happy_path_test, executes_scenario) {
    auto steps = forge_bdd_steps();

    std::cout << "[GIVEN] Given a well-formed YAML configuration file \"config/example.yaml\" that conforms to the schema and has some optional keys missing" << std::endl;
    steps->given_a_well_formed_yaml_configuration_file_config_example_yaml_that_conforms_to_the_schema_and_has_some_optional_keys_missing();
    std::cout << "[WHEN] When the file is loaded into the system" << std::endl;
    steps->when_the_file_is_loaded_into_the_system();
    std::cout << "[THEN] Then the contents are validated against the predefined schema and default values are applied with no errors reported" << std::endl;
    steps->then_the_contents_are_validated_against_the_predefined_schema_and_default_values_are_applied_with_no_errors_reported();
}
