cmake_minimum_required(VERSION 3.26)
project(2023 C)

set(CMAKE_C_STANDARD 11)

add_executable(2023 main.c
    utilities/math.c
    utilities/file.c
    utilities/string.c
    utilities/utilities.h
    solutions/solutions.h
    solutions/01-trebuchet.c
    solutions/02-cubes.c
    solutions/03-gear.c
    solutions/04-scratchcards.c
    solutions/05-seeds.c
    solutions/06-wait.c
    solutions/07-camel.c
    solutions/08-wasteland.c
    solutions/09-mirage.c
    solutions/10-maze.c
    solutions/11-expansion.c
)
