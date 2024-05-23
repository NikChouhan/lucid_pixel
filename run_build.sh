#!/bin/bash

cd build
cmake .. -G Ninja
ninja
cd .. && ./lucid_pixel
cd ..