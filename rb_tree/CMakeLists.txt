cmake_minimum_required(VERSION 3.0)

project(rb_tree_unittest)
add_definitions(-std=c++11)
#set(BASIS_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/../../basis_libs)
#include(${BASIS_LIBS}/global.cmake)

set(BIN_NAME "rbtree_unittest")

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
#aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRCS)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRCS)

list(REMOVE_ITEM SRCS ${CMAKE_CURRENT_SOURCE_DIR}/main.cc)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -std=c++11 -g -Wall")

add_library(common_objs OBJECT ${SRCS})

add_executable(${BIN_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/main.cc" $<TARGET_OBJECTS:common_objs>)

#list(APPEND MY_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/lib.a)

#target_link_libraries(${BIN_NAME} ${MY_LIBS})
