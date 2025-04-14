# forge-core/bdd/CMakeLists.txt

add_executable(print_bdd_runner
    print_bdd.cpp
    runner_main.cpp
)

target_include_directories(print_bdd_runner PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include        # if you need access to forge_core_lib headers
)

target_link_libraries(print_bdd_runner PRIVATE
    forge_core_lib
)

set_target_properties(print_bdd_runner PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)