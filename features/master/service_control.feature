Feature: Control services on agents

  Scenario: Restart service remotely
    Given an agent is running a service
    When the master sends a restart service command
    Then the agent restarts the specified service
    And responds with a status message
