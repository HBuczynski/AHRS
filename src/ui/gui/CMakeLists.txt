# Specify the minimum version of cmake.
cmake_minimum_required(VERSION 3.0)

project(gui)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(PROJECT_NAME gui)
# temp variable
set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt5.8.0/5.8/gcc_64)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Svg)

include_directories(${Qt5_INCLUDE_DIR})
link_directories(${Qt5_LIBRARY_DIRS})

include_directories(../)

link_directories(${CMAKE_BINARY_DIR}/../../lib)

file(GLOB source_list "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/storyboards/*.cpp")
file(GLOB header_list "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/storyboards/*.h")
file(GLOB user_interfaces_list "${CMAKE_CURRENT_SOURCE_DIR}/storyboards/*.ui")

qt5_add_resources(IMG_RSC_ADDED qfi.qrc)

qt5_wrap_ui(UI_GENERATED_HEADERS ${user_interfaces_list})

add_executable(${PROJECT_NAME} ${source_list} ${UI_GENERATED_HEADERS} ${IMG_RSC_ADDED})
#add_library(${PROJECT_NAME} ${source_list} ${UI_GENERATED_HEADERS} ${IMG_RSC_ADDED})
target_include_directories(
    ${PROJECT_NAME} PUBLIC
    # Headers used from source/build location:
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    # Headers used from the installed location:
    "$<INSTALL_INTERFACE:include>"
)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC message_queue_wrapper)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC shared_memory_wrapper)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Svg)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC logger)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC hal)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC switches)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC wireless_commands)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC hm_interface)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC wireless_measurement_commands)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC config_reader)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC gui_interface)

install(TARGETS ${PROJECT_NAME} DESTINATION lib OPTIONAL)
install(FILES ${header_list} DESTINATION include OPTIONAL)

if(BUILD_TESTS)
#    add_subdirectory(unit_tests)
endif()


