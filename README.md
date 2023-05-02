# Picogine

A really small (in size) game engine for 2D games, made originally for the
4Mb Game Jam.

## Building

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
$ CLANG=1 make
$ make compress
```

## License
This project is licensed under the Apache 2.0 License - see the 
[LICENSE](LICENSE) file for details
