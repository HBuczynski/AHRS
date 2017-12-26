# Specify the minimum version of cmake.
cmake_minimum_required(VERSION 3.0)

project(communication_manager_black_box)

set(PROJECT_NAME communication_manager_black_box)
include_directories("../")

file(GLOB source_list "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB header_list "${CMAKE_CURRENT_SOURCE_DIR}/*.h") 

add_library(${PROJECT_NAME} ${source_list} ClientUDPManager.h)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    # Headers used from source/build location:
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    # Headers used from the installed location:
    "$<INSTALL_INTERFACE:include>"
)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC packet)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC protocol)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC client_udp)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC server_tcp)

install(TARGETS ${PROJECT_NAME} DESTINATION lib OPTIONAL)
install(FILES ${header_list} DESTINATION include OPTIONAL)

if(BUILD_TESTS)
    add_subdirectory(unit_tests)
endif()
