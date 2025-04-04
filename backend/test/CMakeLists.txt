cmake_minimum_required(VERSION 3.21)
project(backend_TESTS)

set(CMAKE_CXX_STANDARD )
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# === Global Test Dependencies ===


# === Test Executable ===
add_executable(test_backend
    test_main.cpp
)

target_link_libraries(test_backend PRIVATE
    backend
    gtest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_backend)

set_target_properties(test_backend PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
