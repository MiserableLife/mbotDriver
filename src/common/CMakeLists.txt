
cmake_minimum_required(VERSION 3.7)
#get_property(global_lib_path GLOBAL PROPERTY lib_path )
#set(CMAKE_ 
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${MBOTDRIVER_LIB} )
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

message( "Output Library Path : " ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )
message( "source dir : " ${PROJECT_SOURCE_DIR}	)
message( "source dir : " ${CMAKE_SOURCE_DIR}	)

add_library(mbd_common SHARED 
															logger.cpp
															MBotPacket.cpp
															)
include(GNUInstallDirs) #we will use this later


#install(TARGETS mbd_common DESTINATION ../lib)
