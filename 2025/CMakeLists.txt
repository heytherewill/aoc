cmake_minimum_required(VERSION 3.29)
project(aoc)

set(CMAKE_CXX_STANDARD 26)

add_executable(aoc main.cpp
        solutions/solutions.h
        solutions/solution01_secretentrance.cpp
        utilities/file.h
)
