
set(TEST_INCLUDE "${PROJECT_SOURCE_DIR}/components/basic/designMode")  

include_directories(${TEST_INCLUDE})
link_directories(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_executable(fsm_test ./fsm_test.cpp)
