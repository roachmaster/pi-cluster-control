cmake_minimum_required(VERSION 3.21)
project(pi_cluster_control)

add_library(di_lib
    src/di.cpp
)

target_include_directories(di_lib PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(di_lib PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
