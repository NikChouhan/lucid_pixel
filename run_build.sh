#!/bin/bash

mkdir build
cd build
cmake .. -G Ninja -D CMAKE_CXX_COMPILER=clang++ /usr/bin/clang++ -D CMAKE_C_COMPILER=clang /usr/bin/clang -D CMAKE_EXPORT_COMPILE_COMMANDS=ON
ninja
cd .. && ./lucid_pixel
cd ..