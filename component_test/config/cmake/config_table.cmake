option(BUSSINESS "set if compile bussiness" ON)
if(BUSSINESS)
    option(BUSSINESS_BUSSINESS1 "set if compile bussiness1" ON)
    # add more
endif()

option(BASIC "set if compile basic" ON)
if(BASIC)
    option(BASIC_COMMON "set if compile common" ON)
    # add more
endif()


option(THIRD_PARTS "set if use third-parts" ON)
if(THIRD_PARTS)
    option(THIRD_PARTS_FFMPEG "set if use ffmpeg" ON)
    option(THIRD_PARTS_NCNN "set if use ncnn" ON)
    option(THIRD_PARTS_OPENCV "set if use opencv" ON)
    option(THIRD_PARTS_SPDLOG "set if use spdlog" ON)
    # add more
endif()
