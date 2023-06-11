#!/bin/bash

# This script will build multiple elf for every distro supported.
# This script is not meant to be run by the user, but by the developer.
# Requirements:
# - Docker
# - A working internet connection

# Running the script:
# (From the root of the project) $ ./scripts/multidistro-elf.sh

# Distros targeted:
# - Ubuntu 16.04
# - Ubuntu 18.04
# - Ubuntu 20.04
# - Ubuntu 22.04
# - Alpine latest
# - Fedora latest
# - Debian latest

set -e

OUTPUT_DIR="build_multi"

# Check if we detect README.md
if [ ! -f README.md ]; then
    echo "This script must be run from the root of the project"
    exit 1
fi

# Place the script in the root of the project
# distro, command
docker_run() {
    echo "*** Building for $1"

    # Remove the : and . from the distro name
    local distro=`echo $1 | sed 's/:/-/g' | sed 's/\./-/g'`

    # Run the command in a docker container
    docker run -e P2D_OUTPUT="$OUTPUT_DIR" -e P2D_DISTRO="$distro" \
        --rm -v $(pwd):/potetre2d -w /potetre2d $1 $2

    # Check if the build was successful
    if [ $? -ne 0 ]; then
        echo "Build failed for $1"
        echo "This may happen if you are not connected to the internet or root"
        exit 1
    fi

    echo "*** Build successful for $1"
}

rm -rf $OUTPUT_DIR
mkdir -p $OUTPUT_DIR

# Ubuntu 16.04
docker_run "ubuntu:16.04" "bash ./scripts/multi-distro/ubuntu.sh"

# Ubuntu 18.04
docker_run "ubuntu:18.04" "bash ./scripts/multi-distro/ubuntu.sh"

# Ubuntu 20.04
docker_run "ubuntu:20.04" "bash ./scripts/multi-distro/ubuntu.sh"

# Ubuntu 22.04
docker_run "ubuntu:22.04" "bash ./scripts/multi-distro/ubuntu.sh"

# Ubuntu latest
docker_run "ubuntu:latest" "bash ./scripts/multi-distro/ubuntu.sh"

# Alpine Musl
docker_run "alpine:latest" "sh ./scripts/multi-distro/alpine.sh"

# Fedora 37
docker_run "fedora:latest" "sh ./scripts/multi-distro/fedora.sh"

# Debian 10
docker_run "debian:10" "sh ./scripts/multi-distro/ubuntu.sh"

# Debian latest
docker_run "debian:latest" "sh ./scripts/multi-distro/ubuntu.sh"

echo "**** All builds successful"
