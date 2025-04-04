Feature: frontend runtime behavior

  Scenario: frontend starts up
    Given the frontend module is compiled
    When the frontend binary is executed
    Then it should print "frontend module running..."