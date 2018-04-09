cmake_minimum_required(VERSION 3.9)
project(TM)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.66.0 COMPONENTS regex)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    set(Header TM.hpp Lang.hpp)
    add_executable(TM test.cpp TM.cpp Lang.cpp)
    target_link_libraries(TM ${Boost_LIBRARIES})
endif()

