cmake_minimum_required(VERSION 3.16)
project(raytracer)

include_directories(include)

set(CMAKE_CXX_STANDARD 14)

add_executable(raytracer src/main.cpp src/p3.cpp)