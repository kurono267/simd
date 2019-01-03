cmake_minimum_required(VERSION 3.13)
project(simd)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

set(CMAKE_CXX_STANDARD 14)

add_executable(simd src/test.cpp src/simd/Float4.hpp src/simd/Vec8.hpp src/simd/Vec16.hpp src/simd/Float4.cpp)
target_link_libraries(simd ${Boost_LIBRARIES})
enable_testing ()
