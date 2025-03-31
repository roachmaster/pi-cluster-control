Feature: master runtime behavior

  Scenario: master starts up
    Given the master module is compiled
    When the master binary is executed
    Then it should print "master module running..."