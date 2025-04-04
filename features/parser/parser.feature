Feature: parser runtime behavior

  Scenario: parser starts up
    Given the parser module is compiled
    When the parser binary is executed
    Then it should print "parser module running..."