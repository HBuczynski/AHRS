#!/bin/bash

echo --- BOOST installation ---
sudo apt-get install libboost1.62-all-dev 
sudo apt-get install cmake libblkid-dev e2fslibs-dev libboost-all-dev libaudit-dev

echo --- DOXYGEN installation ---
sudo apt-get install doxygen

echo --- VALGRIND installation ---
sudo apt-get install valgrind
