cmake_minimum_required(VERSION 3.22)
project(exposant_benchmark)

set(CMAKE_CXX_STANDARD 11)

add_executable(exposant_benchmark benchmark.cpp exposant.cpp)
