#!/bin/bash
rm -rf build
rm lab5
mkdir build
cd build
cmake ..
make -j 4
cd ..
./lab5
