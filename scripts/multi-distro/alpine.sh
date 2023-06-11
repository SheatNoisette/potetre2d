apk add python3 make gcc mesa-dev musl-dev freeglut-dev alsa-lib-dev git
make clean
BUILD_DIR="${P2D_OUTPUT}" BIN_NAME="potetre2d-${P2D_DISTRO}" make potetre2d
