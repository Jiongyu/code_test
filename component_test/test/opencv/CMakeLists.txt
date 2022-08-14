
set(OpenCV_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/components/third-part/opencv/include/opencv4/")  
set(OpenCV_LIBRARY_DIRS "${PROJECT_SOURCE_DIR}/components/third-part/opencv/lib/")  
set(OpenCV_DIR "${PROJECT_SOURCE_DIR}/components/third-part/opencv/lib/cmake/opencv4/")  #OpenCVConfig.cmake所在的文件目录
# message("opencv header path:${OpenCV_INCLUDE_DIRS}")
# message("opencv lib path:${OpenCV_LIBRARY_DIRS}")

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

# directory of opencv headers
include_directories(${OpenCV_INCLUDE_DIRS})

# directory of opencv library
link_directories(${OpenCV_LIBRARY_DIRS})

add_executable(opencv_test ./opencv_test.cpp)
target_link_libraries(opencv_test ${OpenCV_LIBS})
