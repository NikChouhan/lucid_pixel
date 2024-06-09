#!/bin/bash

mkdir build
cd build
cmake .. -G Ninja
ninja
cd .. && ./lucid_pixel
cd ..