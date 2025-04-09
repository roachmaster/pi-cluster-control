cmake_minimum_required(VERSION 3.21)
project(pi_cluster_control)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

enable_testing()

# === Global Test Dependencies ===
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

# === Collect All Test Sources ===
file(GLOB_RECURSE TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test_scenario_*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../test_scenario_*.cpp
)
message(STATUS "Test sources: ${TEST_SOURCES}")

# === Test Executable ===
add_executable(test_forge_core_tests ${TEST_SOURCES})

target_link_libraries(test_forge_core_tests PRIVATE
    forge_core_tests_lib
    gtest
    gtest_main
)

# Add the test module's own include directories along with any dependent modules.
target_include_directories(test_forge_core_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

include(GoogleTest)
gtest_discover_tests(test_forge_core_tests)

set_target_properties(test_forge_core_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)