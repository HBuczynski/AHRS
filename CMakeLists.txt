cmake_minimum_required(VERSION 3.0)
project(AHRS)

########################################################################################################
#                                           INITIALIZATION PART                                        #
########################################################################################################

set(CMAKE_BUILD_TYPE Debug)

if(${TARGET_PLATFROM} STREQUAL rpi)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pthread -lwiringPi")
elseif(${TARGET_PLATFROM} STREQUAL virtualBoard)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pthread")
endif()


#TARGET_LINK_LIBRARIES(AHRS_black_box ${CMAKE_THREAD_LIBS_INIT})

# Set the output folder where the program will be created.
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/target/lib)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build_files")

# The following folder will be included
include_directories(src)

########################################################################################################
#                                            ADDING UNIT TESTS                                         #
########################################################################################################
option(BUILD_TESTS "Build the tests" ON)

if(BUILD_TESTS)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    include(CTest)
    enable_testing()
    include(BoostTestHelper)
endif()

#########################################################################################################
#                                           ADDING SUBMODULES                                           #
#########################################################################################################
add_subdirectory("src/time_manager"                                     time_manager                    )
add_subdirectory("src/logger"                                           logger                          )
add_subdirectory("src/protocol"                                         protocol                        )
add_subdirectory("src/utility"                                          utility                         )
add_subdirectory("src/config_reader"                                    config_reader                   )
add_subdirectory("src/packet"                                           packet                          )
add_subdirectory("src/feeder/main_feeder"                               main_feeder                     )
add_subdirectory("src/feeder/server_tcp"                                server_tcp                      )
add_subdirectory("src/feeder/client_udp"                                client_udp                      )
add_subdirectory("src/feeder/communication_manager_feeder"              communication_manager_feeder    )
add_subdirectory("src/ui/client_tcp"                                    client_tcp                      )
add_subdirectory("src/ui/server_udp"                                    server_udp                      )
add_subdirectory("src/ui/communication_manager_ui"                      communication_manager_ui        )
add_subdirectory("src/ui/main_process"                                  main_process                    )
add_subdirectory("src/switches"                                         switches                        )
add_subdirectory("src/hal"                                              hal                             )
add_subdirectory("src/ui/cockpit_gui"                                   cockpit_gui                     )
add_subdirectory("src/ui/communication_process"                         communication_process_ui        )

########################################################################################################
#                                           ADDING DOXYGEN GENERATION                                  #
########################################################################################################

# check if Doxygen is installed
find_package(Doxygen)

if (DOXYGEN_FOUND)
    add_custom_command(OUTPUT ${CMAKE_SOURCE_DIR}/target/docs/documantation/doxygen.stamp
     
        message("Old documantation was removed.")
        COMMAND cmake -E remove_directory ${CMAKE_SOURCE_DIR}/target/docs/documantation/xml
        COMMAND cmake -E remove_directory ${CMAKE_SOURCE_DIR}/target/docs/documantation/html
        COMMAND cmake -E remove_directory ${CMAKE_SOURCE_DIR}/target/docs/documantation/latex

        COMMAND cmake -E make_directory ${CMAKE_SOURCE_DIR}/target/docs/documantation
        COMMAND cmake -E touch ${CMAKE_SOURCE_DIR}/target/docs/documantation/doxygen.stamp

        COMMAND doxygen ${CMAKE_SOURCE_DIR}/build_files/doxygen.config
       
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/.."
        VERBATIM
        )

    add_custom_target(docs DEPENDS ${CMAKE_SOURCE_DIR}/target/docs/documantation/doxygen.stamp)

else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
