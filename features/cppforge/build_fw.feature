Feature: CppForge Build Framework Support

  As a developer
  I want a module that can automate the creation of C++ project scaffolding
  So that I can rapidly set up modules with standard structure, templates, and build files

  Scenario: Bootstrap a new C++ project repository
    Given a valid modules.yaml file exists
    And I run the cppforge bootstrap command
    Then a root-level CMakeLists.txt should be generated
    And it should include all module directories
    And reflect the correct project name and CMake version

  Scenario: Generate a new executable module
    Given a module name "monitor"
    And the module type is "exe"
    When I run the cppforge scaffolding tool
    Then a directory named "monitor" should be created
    And it should contain "CMakeLists.txt"
    And it should contain "src/main.cpp"
    And it should contain an "include/" directory

  Scenario: Generate a new library module
    Given a module name "utils"
    And the module type is "lib"
    When I run the cppforge scaffolding tool
    Then a directory named "utils" should be created
    And it should contain "CMakeLists.txt"
    And it should contain "src/utils.cpp"
    And it should contain "include/utils.hpp"

  Scenario: Generate tests for a module with test: true
    Given the module "network" has test enabled
    When I run the cppforge scaffolding tool
    Then a "test" folder should be created inside the "network" module
    And it should contain "CMakeLists.txt", "test_main.cpp", and "test_network.cpp"

  Scenario: Skip generating tests for a module with test: false
    Given the module "logging" has test disabled
    When I run the cppforge scaffolding tool
    Then no "test" directory should be created for the "logging" module

  Scenario: Re-scaffold updated templates without overwriting custom files
    Given templates have been modified
    And existing module directories contain user changes
    When I run the cppforge regenerate command
    Then only missing or outdated files should be updated
    And custom user files should remain untouched
