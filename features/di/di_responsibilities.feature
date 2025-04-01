Feature: Dependency Injection Module for Pi Cluster Control

  Scenario: Parse source files for DI metadata
    Given a source file with DI macros or annotations
    When the DI module scans the project
    Then it should detect and extract all DI-related tags

  Scenario: Resolve constructor dependencies
    Given a class is annotated for DI
    When the DI module processes the file
    Then it should extract the constructor and identify required dependencies

  Scenario: Register components in the container
    Given extracted class and metadata
    When the DI module generates the container code
    Then it should include bindings for the class and its dependencies

  Scenario: Support singleton and scoped lifetimes
    Given a class is marked with a singleton macro
    When the container is initialized
    Then only one instance of the class should be created and shared

  Scenario: Support template classes and interfaces
    Given a class uses C++ templates
    When the DI parser analyzes it
    Then it should register the concrete implementation against the correct interface

  Scenario: Autowire public methods
    Given a service class has public methods
    When the DI module processes the file
    Then it should collect method signatures for use in code generation

  Scenario: Generate DI registration code before compilation
    Given a module uses DI macros
    When the DI generator runs
    Then it should output registration C++ files used during build time

  Scenario: Validate binding graph for consistency
    Given multiple modules define interdependent services
    When the DI container is generated
    Then it should fail if required bindings are missing or circular

  Scenario: Support testing by mocking dependencies
    Given a class has dependencies
    When running in test mode
    Then the DI system should allow mocks to be injected for isolated testing

  Scenario: Enable debug output for DI resolution
    Given the DI container is in debug mode
    When resolving a class
    Then it should print which concrete implementation was used

