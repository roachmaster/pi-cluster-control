Feature: agent runtime behavior

  Scenario: agent starts up
    Given the agent module is compiled
    When the agent binary is executed
    Then it should print "agent module running..."