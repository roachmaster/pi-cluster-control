Feature: cppforge runtime behavior

  Scenario: cppforge starts up
    Given the cppforge module is compiled
    When the cppforge binary is executed
    Then it should print "cppforge module running..."