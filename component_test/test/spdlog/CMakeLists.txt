
set(SPDLOG_INLCUDE_DIR "${PROJECT_SOURCE_DIR}/components/third-part/spdlog/include/")  
set(SPDLOG_LIBRARY_DIR "${PROJECT_SOURCE_DIR}/components/third-part/spdlog/lib/")  

# message("spdlog header path:${SPDLOG_INLCUDE_DIR}")
# message("spdlog lib path:${SPDLOG_LIBRARY_DIR}")

include_directories(${SPDLOG_INLCUDE_DIR})
link_directories(${SPDLOG_LIBRARY_DIR})

add_executable(sodlog_test ./sodlog_test.cpp)
target_link_libraries(sodlog_test PRIVATE -lspdlog -lpthread)

