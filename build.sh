#!/bin/bash
rm -rf build
rm voxelize
mkdir build
cd build
cmake ..
make -j 4
cd ..
rm -rf textures
mkdir textures
./voxelize
