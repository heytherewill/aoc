cmake_minimum_required(VERSION 3.26)
project(2023 C)

set(CMAKE_C_STANDARD 11)

add_executable(2023 main.c
    utilities/math.h
    utilities/math.c
    utilities/file.h
    utilities/file.c
    utilities/string.h
    utilities/string.c
    solutions/01-trebuchet.h
    solutions/01-trebuchet.c
    solutions/02-cubes.h
    solutions/02-cubes.c
    solutions/03-gear.c
    solutions/03-gear.h
    solutions/04-scratchcards.c
    solutions/04-scratchcards.h)
