# THIS FILE IS AUTO-GENERATED. DO NOT EDIT MANUALLY.

cmake_minimum_required(VERSION 3.21)
project(pi_cluster_control)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === Library Target ===
file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
list(REMOVE_ITEM LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

add_library(backend_lib STATIC ${LIB_SOURCES})

target_include_directories(backend_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# === Executable Target ===
add_executable(backend src/main.cpp)
target_link_libraries(backend PRIVATE backend_lib)

set_target_properties(backend PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
