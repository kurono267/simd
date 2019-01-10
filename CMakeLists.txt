cmake_minimum_required(VERSION 3.13)
project(simd)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -march=skylake-avx512")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=skylake-avx512")

add_executable(simd src/test4.cpp src/simd/Float4.hpp src/simd/Float16.hpp src/test16.cpp)
target_link_libraries(simd ${Boost_LIBRARIES})
enable_testing ()
