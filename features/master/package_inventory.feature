Feature: Collect and compare package inventories

  Scenario: Agent reports installed packages
    Given an agent is registered
    When the master requests a package inventory
    Then the agent returns a list of installed packages

  Scenario: Compare packages across agents
    Given package data from multiple agents
    When the master compares versions
    Then differences in installed packages are reported
