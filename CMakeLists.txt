cmake_minimum_required(VERSION 3.9)
project(TM)

set(CMAKE_CXX_STANDARD 14)

set(Header TM.hpp Lang.hpp)
add_executable(TM test.cpp TM.cpp Lang.cpp)