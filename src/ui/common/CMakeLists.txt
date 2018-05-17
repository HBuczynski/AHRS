# Specify the minimum version of cmake.
cmake_minimum_required(VERSION 3.0)

project(common_ui)

set(PROJECT_NAME common_ui)

include_directories(../)

link_directories(${CMAKE_BINARY_DIR}/../../lib)

file(GLOB source_list "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB header_list "${CMAKE_CURRENT_SOURCE_DIR}/*.h") 

add_library(${PROJECT_NAME} ${source_list} ${header_list})

install(TARGETS ${PROJECT_NAME} DESTINATION lib OPTIONAL)
