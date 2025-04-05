cmake_minimum_required(VERSION 3.21)
project(pi_cluster_control)

add_library(parser_lib
    src/parser.cpp
)

target_include_directories(parser_lib PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(parser_lib PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
