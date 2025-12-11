#!/bin/bash
# rm -r ./build
mkdir build
cd ./build
cmake .. 
make -j12
# ./rbOPVision