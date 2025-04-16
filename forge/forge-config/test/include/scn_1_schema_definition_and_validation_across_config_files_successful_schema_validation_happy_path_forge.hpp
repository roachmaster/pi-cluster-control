#ifndef SCN_1_SCHEMA_DEFINITION_AND_VALIDATION_ACROSS_CONFIG_FILES_SUCCESSFUL_SCHEMA_VALIDATION_HAPPY_PATH_FORGE_HPP
#define SCN_1_SCHEMA_DEFINITION_AND_VALIDATION_ACROSS_CONFIG_FILES_SUCCESSFUL_SCHEMA_VALIDATION_HAPPY_PATH_FORGE_HPP

#include "forge.hpp" // Defines cppforge::core::forge::Forge<T> and NoOpDeleter.
#include "scn_1_schema_definition_and_validation_across_config_files_successful_schema_validation_happy_path_base.hpp"
#include "stub_scn_1_schema_definition_and_validation_across_config_files_successful_schema_validation_happy_path.hpp"
#include <memory>
#include <utility>

namespace cppforge::scenarios {

// Forge for the Successful Schema Validation Scenario.
// It accepts a default (nullable) and a stub (non-null) implementation of the base scenario,
// and its createImpl() method returns the default if available, otherwise the stub.
// The returned unique_ptr uses a NoOpDeleter.
    class Scn1SuccessfulSchemaValidationForge
            : public cppforge::core::forge::Forge<scn_1_schema_definition_and_validation_across_config_files_successful_schema_validation_happy_path_base> {
    private:
        std::shared_ptr<scn_1_schema_definition_and_validation_across_config_files_successful_schema_validation_happy_path_base> defaultImpl; // may be null.
        std::shared_ptr<stub_scn_1_schema_definition_and_validation_across_config_files_successful_schema_validation_happy_path> stubImpl;    // must not be null.

    public:
        // Constructor accepts the two implementations.
        Scn1SuccessfulSchemaValidationForge(
                std::shared_ptr<scn_1_schema_definition_and_validation_across_config_files_successful_schema_validation_happy_path_base> defaultImpl,
                std::shared_ptr<stub_scn_1_schema_definition_and_validation_across_config_files_successful_schema_validation_happy_path> stubImpl)
                : defaultImpl(std::move(defaultImpl)), stubImpl(std::move(stubImpl))
        { }

        // Override of the factory method.
        // Returns a unique_ptr that borrows the instance from the shared_ptr with a NoOpDeleter.
        std::unique_ptr<scn_1_schema_definition_and_validation_across_config_files_successful_schema_validation_happy_path_base, core::forge::NoOpDeleter> createImpl() override {
            if (defaultImpl) {
                return std::unique_ptr<scn_1_schema_definition_and_validation_across_config_files_successful_schema_validation_happy_path_base, core::forge::NoOpDeleter>(defaultImpl.get(), core::forge::NoOpDeleter{});
            } else {
                return std::unique_ptr<scn_1_schema_definition_and_validation_across_config_files_successful_schema_validation_happy_path_base, core::forge::NoOpDeleter>(stubImpl.get(), core::forge::NoOpDeleter{});
            }
        }
    };

} // namespace cppforge::scenarios

#endif // SCN_1_SCHEMA_DEFINITION_AND_VALIDATION_ACROSS_CONFIG_FILES_SUCCESSFUL_SCHEMA_VALIDATION_HAPPY_PATH_FORGE_HPP