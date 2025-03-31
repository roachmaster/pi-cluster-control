cmake_minimum_required(VERSION 3.21)
project(pi_cluster_control)




add_subdirectory(common)
add_subdirectory(tests/agent_tests)
add_subdirectory(agent)
add_subdirectory(master)
add_subdirectory(tests/backend_tests)
add_subdirectory(backend)
