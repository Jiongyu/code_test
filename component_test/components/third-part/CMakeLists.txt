# add_subdirectory(ffmpeg)

# add_subdirectory(opencv)

if(THIRD_PARTS_NCNN)
    add_subdirectory(ncnn)
endif()

if(THIRD_PARTS_SPDLOG)
    add_subdirectory(spdlog)
endif()
# add more library path 
