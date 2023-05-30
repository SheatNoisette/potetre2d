# Building

The project is written in C and supports 64bits platforms only. It is tested on
Linux and Windows.

1. [Building on Linux](#building-on-linux)
  1. [Classic distributions](#classic-distributions)
  2. [Docker](#docker)
  3. [Nix / NixOS](#nix)
2. [Building for Windows](#building-for-windows)
3. [Building on macOS](#building-on-macos)

## Building on Linux
To build on Linux, you need at least to have the following packages installed:
- GCC or Clang which support C20 features
- X11 development libraries
- OpenGL development libraries (GLU and GL)
- Python 3.6 or later
- GNU Make

The following packages are optional:
- UPX (for size optimized builds)

### Classic distributions
On Ubuntu-based systems, you can install them with the following command:
```sh
$ apt-get install -y python3 make build-essential mesa-common-dev \
  libgl1-mesa-dev libglu1-mesa-dev libasound2-dev
```
On Fedora:
```sh
$ dnf install -y python3 make gcc mesa-libGLU-devel mesa-libGL-devel \
  alsa-lib-devel
```
On Alpine:
```sh
$ apk add python3 make gcc mesa-dev musl-dev freeglut-dev alsa-lib-dev
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

If clang and upx is installed, you can also build a agressive size optimized
version:
```
$ CC=clang CLANG=1 make compress
```
**PLEASE NOTE** that the size optimized version MAY BE DETECTED AS A VIRUS by
some antivirus software. This is a false positive. If you don't trust me, you
can build the project yourself and check the source code.
**IT IS RECOMMENDED TO AVOID USING THE SIZE OPTIMIZED VERSION FOR PRODUCTION
PURPOSES.**

### Docker
As a convenience, you can also use Dockerfile to build the project:
```sh
$ docker build -t picogine-dev .
$ docker run -it --rm -v $(pwd):/picogine picogine-dev
(docker) $ (do the same as above)
```

### Nix
If you are using Nix/NixOS, you can also use the provided `flake.nix` file to 
build the project:
```sh
$ nix run
```
The macOS building has not been tested. Please report any issue you may
encounter.

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
$ CC=x86_64-w64-mingw32-gcc CLANG=0 OS=windows make compress
```

## Building on macOS
Please note that you need a Macintosh with XCode command line tools installed 
to build this:
```sh
$ ./bootstrap.sh
$ PYTHON=python3 make
```

Please note that you may need to install a compatible Python version
(3.6 or later) with Homebrew or MacPorts.
```
$ brew install python3
```
If you get an error about `python3` not found, you can try to set the `PYTHON`
make variable to the path of the Python 3 executable.
