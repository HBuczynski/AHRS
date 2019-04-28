# Specify the minimum version of cmake.
cmake_minimum_required(VERSION 3.0)

project(hsm)

set(PROJECT_NAME hsm)
#include_directories("../")

file(GLOB source_list "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB header_list "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_library(${PROJECT_NAME} ${source_list})

target_include_directories(
        ${PROJECT_NAME} PUBLIC
        # Headers used from source/build location:
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        # Headers used from the installed location:
        "$<INSTALL_INTERFACE:include>"
)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC logger)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC time_manager)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC utility)

install(TARGETS ${PROJECT_NAME} DESTINATION lib OPTIONAL)
install(FILES ${header_list} DESTINATION include OPTIONAL)
