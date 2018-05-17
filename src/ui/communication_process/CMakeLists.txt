# Specify the minimum version of cmake.
cmake_minimum_required(VERSION 3.0)

project(communication_process_ui)

set(PROJECT_NAME communication_process_ui)
include_directories("../")

file(GLOB source_list "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB header_list "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_executable(${PROJECT_NAME} ${source_list})

target_include_directories(
        ${PROJECT_NAME} PUBLIC
        # Headers used from source/build location:
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        # Headers used from the installed location:
        "$<INSTALL_INTERFACE:include>"
)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC rt)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC packet)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC communication_manager_ui)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC interprocess_ui_commands)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC wireless_commands)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC wireless_measurement_commands)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC wireless_responses)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC client_tcp)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC server_udp)


install(TARGETS ${PROJECT_NAME} DESTINATION bin OPTIONAL)
install(FILES ${header_list} DESTINATION include OPTIONAL)

