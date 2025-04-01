Feature: Monitor agent heartbeats

  Scenario: Agent sends heartbeat
    Given a registered agent is online
    When the agent sends a heartbeat
    Then the master marks the agent as active

  Scenario: Agent misses heartbeat
    Given a registered agent was previously active
    When no heartbeat is received within the timeout window
    Then the master marks the agent as inactive