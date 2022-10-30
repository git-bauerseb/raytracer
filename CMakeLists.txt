cmake_minimum_required(VERSION 3.16)
project(raytracer)

include_directories(include)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3")

add_executable(raytracer
        src/main.cpp)

target_link_libraries(raytracer pthread sfml-window sfml-graphics sfml-system)