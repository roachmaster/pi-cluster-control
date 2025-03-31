Feature: common runtime behavior

  Scenario: common starts up
    Given the common module is compiled
    When the common binary is executed
    Then it should print "common module running..."