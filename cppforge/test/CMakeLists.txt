add_executable(test_cppforge
test_main.cpp
test_cppforge.cpp
)

target_link_libraries(test_cppforge PRIVATE cppforge)

set_target_properties(test_cppforge PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)