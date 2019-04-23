#cmake_minimum_required(VERSION 3.10)
#find_package(PkgConfig 	REQUIRED)
#pkg_check_modules(BOOST REQUIRED boost)

#include_directories(${BOOST_INCLUDE_DIRS})
#link_libraries(${BOOST_LIBRARIES})
set(CMAKE_BUILD_TYPE Debug)
set(TARGETS server)
set(SRCS 	main.cpp 
					udp_server.cpp
			 		object.cpp 
					observer.cpp)
set(CMAKE_C_COMPILER "clang++")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_executable(${TARGETS} ${SRCS})
target_link_libraries(${TARGETS} pthread
																 boost_system)
