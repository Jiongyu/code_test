include("./config/cmake/compile_env.cmake")
include("./config/cmake/global_set.cmake")
include("./config/cmake/config_table.cmake")

# project name
PROJECT(${project_name})

# requirement of cmake version
cmake_minimum_required(VERSION 3.5)

add_subdirectory(components)

if(COMPILE_TEST)
message(STATUS "Compile test code.")
add_subdirectory(test)
else()
message(STATUS "Not compile test code.")
endif()


# uninstall target
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/config/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()

