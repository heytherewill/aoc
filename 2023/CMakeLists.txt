cmake_minimum_required(VERSION 3.26)
project(2023 C)

set(CMAKE_C_STANDARD 11)

add_executable(2023 main.c
        solutions/01-trebuchet.h
        utilities/file.h
        utilities/string.h)
