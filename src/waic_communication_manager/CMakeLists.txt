# Specify the minimum version of cmake.
cmake_minimum_required(VERSION 3.0)

project(waic_communication_manager)

set(PROJECT_NAME waic_communication_manager)
include_directories("../")

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

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC waic_packet)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC waic_protocol)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC waic_client)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC waic_server)

install(TARGETS ${PROJECT_NAME} DESTINATION lib OPTIONAL)
install(FILES ${header_list} DESTINATION include OPTIONAL)
