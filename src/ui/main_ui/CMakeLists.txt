# Specify the minimum version of cmake.
cmake_minimum_required(VERSION 3.0)

project(main_ui)

set(PROJECT_NAME main_ui)

include_directories(../)

link_directories(${CMAKE_BINARY_DIR}/../../lib)

file(GLOB source_list "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB header_list "${CMAKE_CURRENT_SOURCE_DIR}/*.h") 

add_executable(${PROJECT_NAME} ${source_list})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC logger)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC packet)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC client_tcp)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC server_udp)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC communication_manager_ui)

install(TARGETS ${PROJECT_NAME} DESTINATION bin OPTIONAL)
