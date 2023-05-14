# Building

The project is written in C and support 64bits platforms only. It is tested on
Linux and Windows.

To build on Linux, you need at least to have the following packages installed:
- GCC or Clang which support C20 features
- X11 development libraries
- OpenGL development libraries (GLU and GL)
- Python 3.6 or later
- GNU Make

On Ubuntu-based systems, you can install them with the following command:
```sh
$ apt-get install -y python3 make build-essential mesa-common-dev \
  libgl1-mesa-dev libglu1-mesa-dev
```
On Fedora:
```sh
$ dnf install -y python3 make gcc mesa-libGLU-devel mesa-libGL-devel
```
On Alpine:
```sh
$ apk add python3 make gcc mesa-dev musl-dev freeglut-dev
```

After that, you can build the project with the following commands:
```sh
$ git clone https://github.com/SheatNoisette/picogine.git --recursive
$ cd picogine
$ ./bootstrap.sh
$ make -j
# try it out!
$ ./build/potetre2d.elf examples/fractal.wren
```

As a convenience, you can also use Dockerfile to build the project:
```sh
$ docker build -t picogine-dev .
$ docker run -it --rm -v $(pwd):/picogine picogine-dev
```

If clang and upx is installed, you can also build a agressive size optimized
version:
```
$ CC=clang CLANG=1 make compress
```

## Building for Windows

To build for Windows, you need to have the following packages installed:
- MinGW-w64 GCC
- Upx

On Fedora 37:
```sh
$ dnf install mingw64-gcc
```

Then, you can build the project with the following commands:
```sh
$ ./bootstrap.sh
$ CC=x86_64-w64-mingw32-gcc make compress
```

## Building on macOS

Please note that you need a mac to build this application with XCode
command line tools to build this:
```sh
$ ./bootstrap.sh
$ CC=clang PYTHON=python3 make
```
