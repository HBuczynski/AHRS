#!/bin/bash

cd ../target/bin/
sudo ./hm FEEDER & sleep 1s 
sudo ./main_feeder
