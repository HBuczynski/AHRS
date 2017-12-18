# Specify the minimum version of cmake.
cmake_minimum_required(VERSION 3.0)

project(waic_protocol)

set(PROJECT_NAME waic_protocol)
include_directories("../")

file(GLOB source_list "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB header_list "${CMAKE_CURRENT_SOURCE_DIR}/*.h") 

add_library(${PROJECT_NAME} ${source_list} CommandFactory.cpp CommandFactory.h CommandBuilder.h InitConnectionBuilder.cpp InitConnectionBuilder.h CommandVisitor.h CommandHandler.cpp CommandHandler.h)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    # Headers used from source/build location:
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    # Headers used from the installed location:
    "$<INSTALL_INTERFACE:include>"
)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC time_manager)

install(TARGETS ${PROJECT_NAME} DESTINATION lib OPTIONAL)
install(FILES ${header_list} DESTINATION include OPTIONAL)
