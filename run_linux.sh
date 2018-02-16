#!/bin/bash

# Set basic variables:
# Command name.
input=$1
# Tool name.
tool=$2

target_folder_name="target"

# Create basic target folder.
if [ ! -d $target_folder_name ]; then
    mkdir $target_folder_name
fi

# Execute commands:
if [ "$input" == "test" ]; then

    # Create build and binary files
    cmake . -B"${target_folder_name}"/build
    cmake --build "${target_folder_name}"/build 
    cmake --build "${target_folder_name}"/build -- -j2 test


elif [ "$input" == "doxygen" ]; then   
    # Create build and binary files
    cmake -H. -B"${target_folder_name}"/build
    cmake --build "${target_folder_name}"/build -- -j9 docs
    make install docs

elif [ "$input" == "coverage" ]; then
	if [ ! -d "$target_folder_name"/coverage ]; then
        mkdir "$target_folder_name"/coverage
    fi
    echo "TO DO: coverage"

elif [ "$input" == "clean" ]; then
    rm -r "${target_folder_name}"/

elif [ "$input" == "codeblocks" ]; then
    cmake -G"CodeBlocks - Unix Makefiles" . -B"${target_folder_name}"/build
    cmake --build "${target_folder_name}"/build -- -j3

elif [ "$input" == "Eclipse" ]; then
    cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug . -B"${target_folder_name}"/build
    cmake --build "${target_folder_name}"/build -- -j3 

elif [ "$input" == "help" ]; then

	echo "###########################################"
    echo " "
	echo -----------------  HELP  --------------------
	echo -- Chose one from the following command: --
	echo -------------------------------------------
	echo " --- #test#       : " 
	echo " --- #doxygen#    : "
	echo " --- #coverage#   : "
	echo " --- #clean#      : "
	echo " --- #Codeblocks# : "
	echo " --- #Eclipse#    : "
	echo " --- #help#       : "
    echo " "
	echo "###########################################"

else

	if [ ! -d "$target_folder_name"/docs ]; then
        mkdir "$target_folder_name"/docs
    fi
    
    # Create build and binary files
    cmake . -B"${target_folder_name}"/build
    cmake --build "${target_folder_name}"/build
fi


