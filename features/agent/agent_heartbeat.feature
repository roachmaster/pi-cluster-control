Feature: Agent heartbeat
  Scenario: Agent sends heartbeat
    Given the agent is running
    When 5 seconds pass
    Then it should publish a heartbeat signal to the master
