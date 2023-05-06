#!/bin/sh

# Detect Python
if command -v python3 &>/dev/null; then
    python=python3
elif command -v python &>/dev/null; then
    python=python
else
    echo "Python not found"
    exit 1
fi

echo "Fetching recursively modules..."
git submodule update --init --recursive

echo "Bootstraping Wren..."
mkdir -p external/wren/build
cd external/wren;$python util/generate_amalgamation.py > build/wren.c
