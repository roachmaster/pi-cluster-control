cmake_minimum_required(VERSION )
project()

set(CMAKE_CXX_STANDARD )
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(_lib
)


target_include_directories(_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(_lib PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)