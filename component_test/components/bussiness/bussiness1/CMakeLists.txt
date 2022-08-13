include(${PROJECT_SOURCE_DIR}/config/cmake/global_set.cmake)

string(REGEX REPLACE "/$" "" CURRENT_FOLDER_ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR})
string(REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CURRENT_FOLDER_ABSOLUTE})
# MESSAGE (STATUS ${CURRENT_FOLDER})

string(REGEX REPLACE "(.*)/${CURRENT_FOLDER}$" "\\1" SECOND_FOLDER_ABSOLUTE ${CURRENT_FOLDER_ABSOLUTE})
string(REGEX REPLACE ".*/(.*)" "\\1" SECOND_FOLDER ${SECOND_FOLDER_ABSOLUTE})
# MESSAGE (STATUS ${SECOND_FOLDER})

# library name
set(lib_name ${SECOND_FOLDER}-${CURRENT_FOLDER})

# library version
set(lib_big_v 1)
set(lib_medium_v 1)
set(lib_small_v 1)

# library header file direction
include_directories(include)
include_directories(${PROJECT_SOURCE_DIR}/components/basic/common/include)

# library source
set(lib_src 
    src/bussiness1.cpp)

# shared library
ADD_LIBRARY(${lib_name} SHARED ${lib_src})
SET_TARGET_PROPERTIES(${lib_name} PROPERTIES  OUTPUT_NAME ${lib_name})
SET_TARGET_PROPERTIES(${lib_name} PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(${lib_name} PROPERTIES VERSION ${lib_big_v}.${lib_medium_v}.${lib_small_v})

## installing
# Library
install (TARGETS ${lib_name}
    DESTINATION ${OPTPUT_PATH}${SECOND_FOLDER}/${CURRENT_FOLDER}/lib)

# Header files
install(DIRECTORY ./include/ 
    DESTINATION ${OPTPUT_PATH}${SECOND_FOLDER}/${CURRENT_FOLDER}/include)
