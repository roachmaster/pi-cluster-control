Feature: di runtime behavior

  Scenario: di starts up
    Given the di module is compiled
    When the di binary is executed
    Then it should print "di module running..."