cmake_minimum_required(VERSION 3.21)
project(pi_cluster_control)

add_library(forge_templates_lib
    src/forge_templates.cpp
)

target_include_directories(forge_templates_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(forge_templates_lib PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
