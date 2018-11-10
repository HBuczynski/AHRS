# Specify the minimum version of cmake.
cmake_minimum_required(VERSION 3.0)

project(external_feeder_communication)

set(PROJECT_NAME external_feeder_communication)
include_directories("../")

file(GLOB source_list "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/machine_state/*.cpp")
file(GLOB header_list "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/machine_state/*.h")

add_executable(${PROJECT_NAME} ${source_list})

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    # Headers used from source/build location:
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    # Headers used from the installed location:
    "$<INSTALL_INTERFACE:include>"
)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC message_queue_wrapper)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC logger)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC time_manager)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC config_reader)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC packet)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC communication_process_feeder)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC wireless_commands)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC wireless_measurement_commands)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC wireless_responses)


install(TARGETS ${PROJECT_NAME} DESTINATION lib OPTIONAL)
install(FILES ${header_list} DESTINATION include OPTIONAL)

if(BUILD_TESTS)
    #add_subdirectory(unit_tests)
endif()
