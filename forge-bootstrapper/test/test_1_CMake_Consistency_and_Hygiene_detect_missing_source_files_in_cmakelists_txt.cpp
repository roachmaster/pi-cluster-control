#include <gtest/gtest.h>
#include <iostream>
#include <memory>

// Step Interface
class scn_1_cmake_consistency_and_hygiene_detect_missing_source_files_in_cmakelists_txt {
public:
    virtual void given_a_module_has_source_files_not_listed_in_its_cmakelists_txt() {
        FAIL() << "[STEP NOT IMPLEMENTED] Given a module has source files not listed in its CMakeLists.txt";
    }
    virtual void when_i_run_cppforge_validate() {
        FAIL() << "[STEP NOT IMPLEMENTED] When I run cppforge validate";
    }
    virtual void then_it_should_report_the_missing_source_file_references() {
        FAIL() << "[STEP NOT IMPLEMENTED] Then it should report the missing source file references";
    }

    virtual ~scn_1_cmake_consistency_and_hygiene_detect_missing_source_files_in_cmakelists_txt() = default;
};

// Stub Implementation (throws failures)
class stub_scn_1_cmake_consistency_and_hygiene_detect_missing_source_files_in_cmakelists_txt : public scn_1_cmake_consistency_and_hygiene_detect_missing_source_files_in_cmakelists_txt {
    // No overrides – just uses FAIL() behavior from base class
};

#ifdef HAS_IMPL_scn_1_cmake_consistency_and_hygiene_detect_missing_source_files_in_cmakelists_txt
static std::unique_ptr<scn_1_cmake_consistency_and_hygiene_detect_missing_source_files_in_cmakelists_txt> forge_bdd_steps() {
    return std::make_unique<impl_scn_1_cmake_consistency_and_hygiene_detect_missing_source_files_in_cmakelists_txt>();
}
#else
static std::unique_ptr<scn_1_cmake_consistency_and_hygiene_detect_missing_source_files_in_cmakelists_txt> forge_bdd_steps() {
    return std::make_unique<stub_scn_1_cmake_consistency_and_hygiene_detect_missing_source_files_in_cmakelists_txt>();
}
#endif

// Test Case
TEST(scn_1_cmake_consistency_and_hygiene_detect_missing_source_files_in_cmakelists_txt_test, executes_scenario) {
    auto steps = forge_bdd_steps();

    std::cout << "[GIVEN] Given a module has source files not listed in its CMakeLists.txt" << std::endl;
    steps->given_a_module_has_source_files_not_listed_in_its_cmakelists_txt();
    std::cout << "[WHEN] When I run cppforge validate" << std::endl;
    steps->when_i_run_cppforge_validate();
    std::cout << "[THEN] Then it should report the missing source file references" << std::endl;
    steps->then_it_should_report_the_missing_source_file_references();
}
