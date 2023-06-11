#!/bin/bash

apt-get update
apt-get install -y python3 make build-essential mesa-common-dev \
  libgl1-mesa-dev libglu1-mesa-dev libasound2-dev git
make clean

echo "Output: $P2D_OUTPUT"

# P2D_OUTPUT is a environement variable set by the docker container
PYTHON=python3 BUILD_DIR="${P2D_OUTPUT}" BIN_NAME="potetre2d-${P2D_DISTRO}" make potetre2d
