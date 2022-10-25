# Raytracer

This is a simple raytracer written in C++

## About

Current render output:

![Render output](./resources/img.png)

Some difficulties with refraction:
![Another render output](./resources/img_dielectric.png)

Another render:
![Yet another render output](./resources/img_current.png)

## TODO

- [ ] Make multithreaded for faster rendering
- [ ] Add REPL interpreter for interactive rendering

## Setup

```shell
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./raytracer
```