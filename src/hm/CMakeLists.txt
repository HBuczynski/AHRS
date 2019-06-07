# Specify the minimum version of cmake.
cmake_minimum_required(VERSION 3.0)

project(hm)

set(PROJECT_NAME hm)

include_directories(../)

link_directories(${CMAKE_BINARY_DIR}/../../lib)

file(GLOB source_list "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" )
file(GLOB header_list "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_executable(${PROJECT_NAME} ${source_list})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC message_queue_wrapper)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC hm_interface)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC logger)


install(TARGETS ${PROJECT_NAME} DESTINATION bin OPTIONAL)
