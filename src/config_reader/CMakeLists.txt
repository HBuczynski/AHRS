# Specify the minimum version of cmake.
cmake_minimum_required(VERSION 3.0)

project(config_reader)

set(PROJECT_NAME config_reader)
include_directories("../")
include_directories("../../3rd_party/json/")
include_directories("../../3rd_party/json/json")

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

#add_custom_command(TARGET config_reader PRE_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_SOURCE_DIR}/unit_tests/test_files $<TARGET_FILE_DIR:config_reader>)

add_library(jsonlib STATIC "../../3rd_party/json/jsoncpp.cpp"
                        "../../3rd_party/json/json/json.h"
                        "../../3rd_party/json/json/json-forwards.h")

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC logger)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC jsonlib)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC hal)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC time_manager)

install(TARGETS ${PROJECT_NAME} DESTINATION lib OPTIONAL)
install(FILES ${header_list} DESTINATION include OPTIONAL)

if(BUILD_TESTS)
    add_subdirectory(unit_tests)
endif()
