cmake_minimum_required(VERSION 3.21)
project(pi_cluster_control)

set(CMAKE_CXX_STANDARD )
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(forge_core_tests_lib
    src/forge_core_tests.cpp
)

target_include_directories(forge_core_tests_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/forge-core/include
)

set_target_properties(forge_core_tests_lib PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)