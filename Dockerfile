FROM ubuntu:22.04

RUN apt-get update
RUN apt-get install -y python3 make build-essential clang \
          mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev bash upx \
          gcc-mingw-w64 libasound2-dev

ENTRYPOINT ["/bin/bash"]
