cmake_minimum_required(VERSION 3.7)
#find_package(PkgConfig 	REQUIRED)
#pkg_check_modules(BOOST REQUIRED boost)

#include_directories(${BOOST_INCLUDE_DIRS})
#link_libraries(${BOOST_LIBRARIES})
#find_package(PkgConfig REQUIRED)
#pkg_check_modules(OPENCV REQUIRED opencv)

#include_directories(${OPENCV_INCLUDE_DIRS})
#link_libraries(${OPENCV_LIBRARIES})
set(CMAKE_BUILD_TYPE Debug)
set(TARGETS udpserver)
set(SRCS 	
					udp_server.cpp)
set(CMAKE_C_COMPILER "clang++")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY output)

add_library(${TARGETS} ${SRCS})
target_link_libraries(${TARGETS} pthread
																 boost_system
																 mbd_common)
																 #																 ${OPENCV_LIBRARIES})
