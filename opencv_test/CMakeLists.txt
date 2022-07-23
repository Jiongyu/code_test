# project name
PROJECT(opencv_test)
# requirement of cmake version
cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_BUILD_TYPE "Debug")
set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# set the directory of executable files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${opencv_test_SOURCE_DIR}/bin)

set(OpenCV_DIR "/home/jony/software/opencv/opencv/build")  #OpenCVConfig.cmake所在的文件目录
set(NCNN_DIR "/mnt/hgfs/ubuntu20/open_source_proj/ncnn/src/"
    "/mnt/hgfs/ubuntu20/open_source_proj/ncnn/build-ubuntu/src/")  #ncnnCVConfig.cmake所在的文件目录

# find required opencv
find_package(OpenCV REQUIRED)
# directory of opencv headers
include_directories(${OpenCV_INCLUDE_DIRS})
# name of executable file and path of source file
add_executable(opencv_test ./opencv_test.cpp)
# directory of opencv library
link_directories(${OpenCV_LIBRARY_DIRS})
# opencv libraries
target_link_libraries(opencv_test ${OpenCV_LIBS})

add_executable(opencv_camera_test ./opencv_camera_test.cpp)
target_link_libraries(opencv_camera_test ${OpenCV_LIBS})

include_directories(${NCNN_DIR})
link_directories(${NCNN_DIR})
add_executable(ncnn_yolov5_test ./ncnn_yolov5.cpp)
target_link_libraries(ncnn_yolov5_test ${OpenCV_LIBS} ncnn -lpthread -lm -fopenmp) 

add_executable(opencv_camera_yolov5 ./opencv_camera_yolov5.cpp)
target_link_libraries(opencv_camera_yolov5  ncnn -lpthread -lm -fopenmp ${OpenCV_LIBS})

MESSAGE(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "OpenCV_DIR : ${OpenCV_DIR}")
message(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")
MESSAGE(STATUS "OpenCV_LIBS : ${OpenCV_VERSION}")
