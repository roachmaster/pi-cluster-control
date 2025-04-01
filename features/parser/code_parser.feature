Feature: C++ Source Code Parser

  This module parses C++ source files to extract metadata for use in the DI container.
  It locates macro annotations, captures constructor dependencies, and gathers public methods.

  Scenario: Parse a source file containing annotated classes
    Given a C++ source file with DI-related macros
    When the parser scans the file
    Then it should identify all classes annotated with DI macros
    And it should extract each class's constructor dependencies
    And it should collect all public methods in each class

  Scenario: Handle nested namespaces and multiple classes
    Given a C++ source file with nested namespaces and multiple class definitions
    When the parser processes the file
    Then it should group classes by their full namespace path
    And accurately extract constructor dependencies and methods per class

  Scenario: Detect invalid or missing annotations
    Given a C++ source file with incorrect or missing macro annotations
    When the parser scans the file
    Then it should ignore those classes or report a warning
    And it should continue processing the rest of the file

  Scenario: Output intermediate JSON metadata
    Given a valid annotated source file
    When parsing completes
    Then the parser should emit a JSON file with class metadata
    And the JSON should include class name, namespace, dependencies, and public methods

  Scenario: Support header and implementation file pairs
    Given a pair of header (.hpp) and implementation (.cpp) files
    When the parser processes them together
    Then it should merge metadata from both files
    And associate method definitions in .cpp with declarations in .hpp
