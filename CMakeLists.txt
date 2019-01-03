cmake_minimum_required(VERSION 3.13)
project(simd)

set(CMAKE_CXX_STANDARD 14)

add_executable(simd src/main.cpp src/simd/Vec4.hpp src/simd/Vec8.hpp src/simd/Vec16.hpp src/simd/Vec4.cpp)