cmake_minimum_required(VERSION 3.21)
project(pi_cluster_control)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(forge_core_lib
    src/forgeable_scenario_provider.cpp
    src/scenario_forge_test.cpp
    src/forge_core.cpp
)

target_include_directories(forge_core_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(forge_core_lib PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)