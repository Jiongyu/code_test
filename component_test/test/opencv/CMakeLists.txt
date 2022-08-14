
set(OpenCV_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/components/third-part/opencv/include/opencv4/")  
set(OpenCV_LIBRARY_DIRS "${PROJECT_SOURCE_DIR}/components/third-part/opencv/lib/")  

message("opencv header path:${OpenCV_INCLUDE_DIRS}")
message("opencv lib path:${OpenCV_LIBRARY_DIRS}")

# directory of opencv headers
include_directories(${OpenCV_INCLUDE_DIRS})

# directory of opencv library
link_directories(${OpenCV_LIBRARY_DIRS})

add_executable(opencv_test ./opencv_test.cpp)
target_link_libraries(opencv_test 
    -lopencv_features2d 
    -lopencv_imgcodecs
    -lopencv_core
    -lpthread
)
