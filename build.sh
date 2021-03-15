#!/bin/bash
# Create Release directory and build soft
###########################################
mkdir Release
cd Release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
