cmake_minimum_required(VERSION 3.14)
project(cppforge_tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Download GoogleTest
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

# Make available
FetchContent_MakeAvailable(googletest)

# === Test Executable ===
add_executable(
        test_cppforge
        test_bootstrap.cpp
)
target_sources(test_cppforge PRIVATE
        test_generate_executable_module.cpp
)
# Link GoogleTest and cppforge module
target_link_libraries(
        test_cppforge
        PRIVATE
        cppforge
        gtest
        gtest_main
)

# === Automatically Discover Tests ===
include(GoogleTest)
gtest_discover_tests(test_cppforge)

# Set output directory for test binary
set_target_properties(test_cppforge PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)