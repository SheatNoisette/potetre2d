# Picogine

A really small (in size) game engine for 2D games, made originally for the
4Mb Game Jam.

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
$ CLANG=1 make compress
```

## License
This project is licensed under the Apache 2.0 License - see the 
[LICENSE](LICENSE) file for details
