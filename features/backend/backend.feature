Feature: backend runtime behavior

  Scenario: backend starts up
    Given the backend module is compiled
    When the backend binary is executed
    Then it should print "backend module running..."