cmake_minimum_required(VERSION 2.8.9)

#
# Common settings
#

# adds ./include to compiler include directories
include_directories(include)
# compiles code files from ./src folder
file(GLOB LIB_SOURCES "src/*.c")

#
# first project (static lib)
#

#
# Second project (executable)
#
project(a.out)
# to build executable target with name a.out
add_executable(${CMAKE_PROJECT_NAME} "server.c" ${LIB_SOURCES})



# uncomment this to link libxml2 XML library
# target_link_libraries(${CMAKE_PROJECT_NAME} libxml2.so)

# uncomment this to link jansson JSON library
 target_link_libraries(${CMAKE_PROJECT_NAME} libjansson.so progbase ssl)
 target_link_libraries(${CMAKE_PROJECT_NAME} event)
 include_directories(/usr/local/include)

# uncomment to use libxml2 XML headers
# include_directories(/usr/include/libxml2)