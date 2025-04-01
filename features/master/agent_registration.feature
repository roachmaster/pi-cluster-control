Feature: Register new agent

  Scenario: Agent initiates registration
    Given an agent connects to the master for the first time
    When the agent sends registration metadata
    Then the master stores the agent info
    And responds with a success acknowledgement