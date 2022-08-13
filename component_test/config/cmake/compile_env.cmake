# 编译器环境
set(cross_compiler "")
set(CMAKE_C_COMPILER "${cross_compiler}gcc")
set(CMAKE_CXX_COMPILER "${cross_compiler}g++")
set(CMAKE_CXX_STANDARD 11)

set(CXX_FLAGS
 # -DVALGRIND
 -DCHECK_PTHREAD_RETURN_VALUE
 -D_FILE_OFFSET_BITS=64
 -Wall
 -Wextra
 -Werror
 -Wconversiondddd
 -Wno-unused-parameter
 -Wold-style-cast
 -Woverloaded-virtual
 -Wpointer-arith
 -Wshadow
 -Wwrite-strings
 -march=native
 # -MMD
 -std=c++11
 -rdynamic
 )

# 编译模式
SET(CMAKE_BUILD_TYPE "Debug")
# SET(CMAKE_BUILD_TYPE "Release")

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")
    set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")

elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
else()
    message("unknow compile type.")
endif()


