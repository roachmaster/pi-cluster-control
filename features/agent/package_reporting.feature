Feature: Package reporting
  Scenario: Agent lists all packages
    Given the agent is running
    When it scans for installed packages
    Then it should return a full list of all installed packages

  Scenario: Agent lists simplified packages
    Given the agent is configured with a simplified list
    When it scans for installed packages
    Then it should return only the configured subset
