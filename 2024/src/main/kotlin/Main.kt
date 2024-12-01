package com.heytherewill

import com.heytherewill.solutions.HistorianHysteria

val solutions = listOf(
    HistorianHysteria()
)

fun main() {

    print("                -                \n");
    print("               ---               \n");
    print("             --*----             \n");
    print("           -------*---           \n");
    print("         ------*---*----         \n");
    print("       ---O----------O----       \n");
    print("     -------*---O-----*-----     \n");
    print("   ----O-----*------*---------   \n");
    print(" ---------O------*-----------*-- \n");
    print("---------------------------------\n");
    print("|     Advent of Code   2024     |\n");
    print("|-------------------------------|\n");
    for (solution in solutions) {
        print("|Problem ${solution.day} (${solution.name}) |\n");
        print("|-------------------------------|\n");
        print("| I: ${solution.solvePartOne()}   |  II: ${solution.solvePartTwo()}  |\n")
    }
}