# Specify the minimum version of cmake.
cmake_minimum_required(VERSION 3.0)

project(internal_feeder_communication)
set(PROJECT_NAME internal_feeder_communication)

include_directories(../)
link_directories(${CMAKE_BINARY_DIR}/../../lib)

file(GLOB source_list "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB header_list "${CMAKE_CURRENT_SOURCE_DIR}/*.h") 

add_executable(${PROJECT_NAME} ${source_list})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC packet)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC shared_memory_wrapper)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC message_queue_wrapper)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC logger)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC time_manager)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC wireless_commands)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC hm_interface)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC wireless_measurement_commands)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC wireless_responses)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC communication_process_feeder)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ethernet_feeder)

install(TARGETS ${PROJECT_NAME} DESTINATION lib OPTIONAL)
install(FILES ${header_list} DESTINATION include OPTIONAL)
