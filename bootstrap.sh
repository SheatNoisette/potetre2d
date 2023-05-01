#!/bin/sh

echo "Fetching recursively modules..."
git submodule update --init --recursive

echo "Bootstraping Wren..."
mkdir -p external/wren/build
cd external/wren;python util/generate_amalgamation.py > build/wren.c
