# Potetre2d

L'as tu faite? Potetre
---

A really small (in size) game engine for 2D games, made originally for the
4Mb Game Jam. We were disappointed by the lack of 2D game engine that could
fit in 4Mb, so we made one. The objective of this project is to make a Löve2D
like engine, but with a smaller footprint. We didn't wanted to write bare
C code, so any game written with this engine will be written in Wren.

## Building

To build on Linux, you need at least to have the following packages installed:
- GCC or Clang which support C20 features
- X11 development libraries
- OpenGL development libraries (GLU and GL)
- Python 3.6 or later
- GNU Make

On Ubuntu-based systems, you can install them with the following command:
```
$ apt-get install -y python3 make build-essential mesa-common-dev \
  libgl1-mesa-dev libglu1-mesa-dev
```
On Fedora:
```
$ dnf install -y python3 make gcc mesa-libGLU-devel mesa-libGL-devel
```

After that, you can build the project with the following commands:
```
$ git clone https://github.com/SheatNoisette/picogine.git --recursive
$ cd picogine
$ ./bootstrap.sh
$ make -j
```

As a convenience, you can also use Dockerfile to build the project:
```
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
```
$ dnf install mingw64-gcc
```

Then, you can build the project with the following commands:
```
$ ./bootstrap.sh
$ CC=x86_64-w64-mingw32-gcc make compress
```

## Building on macOS

Please note that you need a mac to build this application with XCode
command line tools to build this:
```
$ ./bootstrap.sh
$ CC=clang PYTHON=python3 make
```

## License
This project is licensed under the Apache 2.0 License - see the
[LICENSE](LICENSE) file for details
