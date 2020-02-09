cmake_minimum_required(VERSION 3.7)
#find_package(PkgConfig 	REQUIRED)
#pkg_check_modules(BOOST REQUIRED boost)

#include_directories(${BOOST_INCLUDE_DIRS})
#link_libraries(${BOOST_LIBRARIES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENCV REQUIRED opencv)
add_subdirectory(tcpserver)
add_subdirectory(udpserver)


link_libraries(${OPENCV_LIBRARIES})
set(CMAKE_BUILD_TYPE Debug)
set(TARGETS server)
set(SRCS 	main.cpp )
set(CMAKE_C_COMPILER "clang++")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_executable(${TARGETS} ${SRCS})
include_directories( udpserver tcpserver)
target_link_libraries(${TARGETS} 	udpserver
																	tcpserver
																 )
