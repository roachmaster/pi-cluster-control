cmake_minimum_required(VERSION 3.21)
project(pi_cluster_control)

add_library(forge_parser_lib
    src/forge_parser.cpp
)

target_include_directories(forge_parser_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(forge_parser_lib PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
