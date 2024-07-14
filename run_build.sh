#!/bin/bash

mkdir build
cd build
cmake .. -G Ninja -D CMAKE_CXX_COMPILER=clang++ /usr/bin/clang++
ninja
cd .. && ./lucid_pixel
cd ..