cmake_minimum_required(VERSION 2.8)
project(Z5)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
add_executable(x main.cpp render.cpp Shape.h Sphere.h VecPoint.h Clmg.h Box.h)