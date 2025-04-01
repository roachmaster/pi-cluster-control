add_executable(test_parser
test_main.cpp
test_parser.cpp
)

target_link_libraries(test_parser PRIVATE parser)

set_target_properties(test_parser PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)