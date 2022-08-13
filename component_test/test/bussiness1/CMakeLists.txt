
set(TEST_INCLUDE "${PROJECT_SOURCE_DIR}/components/bussiness/bussiness1/include/"
"${PROJECT_SOURCE_DIR}/components/basic/common/include")  

include_directories(${TEST_INCLUDE})
link_directories(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_executable(bussiness_test1 ./bussiness_test1.cpp)
target_link_libraries(bussiness_test1 -lbussiness-bussiness1 -lbasic-common)

