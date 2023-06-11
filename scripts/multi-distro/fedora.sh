dnf install -y python3 make gcc mesa-libGLU-devel mesa-libGL-devel \
  alsa-lib-devel git
make clean
PYTHON=python3 BUILD_DIR="${P2D_OUTPUT}" BIN_NAME="potetre2d-${P2D_DISTRO}" make potetre2d
