Feature: Execute commands on remote agent

  Scenario: Execute shell command on a single agent
    Given an active agent is registered
    When the master sends a shell command to the agent
    Then the agent executes the command
    And returns the output to the master

  Scenario: Execute command on multiple agents
    Given multiple agents are registered
    When the master sends a batch command
    Then each agent executes the command
    And each response is collected by the master