# Specify the minimum version of cmake.
cmake_minimum_required(VERSION 3.0)

project(main_ui)

set(PROJECT_NAME main_ui)

include_directories(../)

link_directories(${CMAKE_BINARY_DIR}/../../lib)

file(GLOB source_list "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/machine_state/*.cpp")
file(GLOB header_list "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/machine_state/*.h")

add_executable(${PROJECT_NAME} ${source_list})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC database_manager)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC message_queue_wrapper)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC shared_memory_wrapper)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC hsm)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC logger)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC wireless_commands)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC wireless_responses)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC communication_process_ui)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC gui_interface)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC switches)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC packet)


install(TARGETS ${PROJECT_NAME} DESTINATION bin OPTIONAL)
