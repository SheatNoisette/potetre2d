from ubuntu:22.04

RUN apt update
RUN apt install -y python3 make build-essential clang \
    mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev bash

ENTRYPOINT ["/bin/bash"]
