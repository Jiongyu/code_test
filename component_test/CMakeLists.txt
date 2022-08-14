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
