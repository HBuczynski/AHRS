#!/bin/bash

target_folder="../tshark_out"

if [ ! -d $target_folder ]; then
    mkdir $target_folder
fi

cd $target_folder

NOW=$(date +"%Y.%m.%d_%I:%M:%p")
fileName="log_$NOW.pcap"

tshark -q -ni any -w $fileName &

