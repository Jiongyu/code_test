set(project_name component_demo)

set(OPTPUT_PATH ${PROJECT_SOURCE_DIR}/output/)

# set the directory of executable files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${${project_name}_SOURCE_DIR}/output/tmp/bin)

# set the directory of dynamic librarys
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${${project_name}_SOURCE_DIR}/output/tmp/lib)

# set the directory of static librarys
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${${project_name}_SOURCE_DIR}/output/tmp/lib)

# set if compile test code
# set(COMPILE_TEST OFF)
option(COMPILE_TEST "set if compile test code" OFF)
