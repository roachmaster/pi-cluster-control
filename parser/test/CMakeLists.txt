cmake_minimum_required(VERSION 3.21)
project(parser_TESTS)

set(CMAKE_CXX_STANDARD )
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# === Global Test Dependencies ===


# === Test Executable ===
add_executable(test_parser
    test_main.cpp
)

target_link_libraries(test_parser PRIVATE
    parser
    gtest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_parser)

set_target_properties(test_parser PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
