cmake_minimum_required(VERSION 3.0)

project(RTIMULib)

set(PROJECT_NAME RTIMULib)

file(GLOB source_list "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/IMUDrivers/*.cpp")
file(GLOB header_list "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/IMUDrivers/*.h")

add_library(${PROJECT_NAME} ${source_list})

target_include_directories(
        ${PROJECT_NAME} PUBLIC
        # Headers used from source/build location:
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        # Headers used from the installed location:
        "$<INSTALL_INTERFACE:include>"
)

install(TARGETS ${PROJECT_NAME} DESTINATION lib OPTIONAL)
