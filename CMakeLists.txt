cmake_minimum_required(VERSION 3.0)
project(AHRS_black_box)

###############################################################
#                  INITIALIZATION PART                        #
###############################################################

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

#TARGET_LINK_LIBRARIES(AHRS_black_box ${CMAKE_THREAD_LIBS_INIT})

# Set the output folder where the program will be created.
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/target/lib)

# The following folder will be included
include_directories(src)

###############################################################
#                  ADDING SUBMODULES                          #
###############################################################
add_subdirectory("src/utility"          utility )
add_subdirectory("src/time_manager"     time_manager)
add_subdirectory("src/logger"           logger)
add_subdirectory("src/config_reader"    config_reader)
add_subdirectory("src/waic_packet"      waic_packet)
add_subdirectory("src/waic_protocol"    waic_protocol)
add_subdirectory("src/waic_server"      waic_server)
add_subdirectory("src/waic_client"      waic_client)
add_subdirectory("src/main_project"     main_project)


###############################################################
#                  ADDING DOXYGEN GENERATION                  #
###############################################################
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

###############################################################
#                  ADDING UNIT TESTS                          #
###############################################################



