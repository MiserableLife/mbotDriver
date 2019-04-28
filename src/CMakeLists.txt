cmake_minimum_required(VERSION 3.7)

project(mbotDriver)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(MBOTDRIVER_LIB ${PROJECT_SOURCE_DIR}/lib CACHE PATH "library path")
#set_property(GLOBAL PROPERTY lib_path ${MBOTDRIVER_LIB})
#message(${PROJECT_SOURCE_DIR})
#message(${CMAKE_BINARY_DIR})
#message(${MBOTDRIVER_LIB})
include_directories(common)
#include_directories(.)

add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(udpserver)

#add_dependencies(udpserver common)
#add_dependencies(client common)
