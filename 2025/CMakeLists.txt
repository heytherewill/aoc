cmake_minimum_required(VERSION 3.29)
project(aoc)

set(CMAKE_CXX_STANDARD 26)

add_executable(aoc main.cpp
        solutions/solutions.h
        utilities/file.h
        solutions/solution01_secretentrance.cpp
        solutions/solution02_giftshop.cpp
        solutions/solution03_lobby.cpp
        solutions/solution04_printingdepartment.cpp
)
