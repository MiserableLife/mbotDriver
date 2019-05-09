
set(TARGETS client)
set(SRCS Client.cpp)
set(CMAKE_C_COMPILER "clang++")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_BUILD_TYPE Debug)

#add_executable(${TARGETS} ${SRCS})
add_library(${TARGETS} ${SRCS})
target_link_libraries(${TARGETS} boost_system
																 pthread
																 mbd_common)

