package com.heytherewill

import com.heytherewill.solutions.HistorianHysteria
import com.heytherewill.solutions.RedNosedReports

private val solutions = listOf(
    HistorianHysteria(),
    RedNosedReports()
)

private const val lineInternalSpace = 31
private val separationText = List(lineInternalSpace) { "-" }.joinToString("")

private fun printLineWithPadding(text: String) {
    val totalPadding = lineInternalSpace - text.length
    val halfPadding = totalPadding / 2
    val paddingLeft = List(halfPadding) { " " }.joinToString("")
    val paddingRight = List(totalPadding - halfPadding) { " " }.joinToString("")

    print("|${paddingLeft}${text}${paddingRight}|\n")
}

private fun printTreeSeparator() {
    print("|${separationText}|\n")
}

fun main() {

    print("                -                \n")
    print("               ---               \n")
    print("             --*----             \n")
    print("           -------*---           \n")
    print("         ------*---*----         \n")
    print("       ---O----------O----       \n")
    print("     -------*---O-----*-----     \n")
    print("   ----O-----*------*---------   \n")
    print(" ---------O------*-----------*-- \n")
    print("---------------------------------\n")
    printLineWithPadding("Advent of Code 2024")
    printTreeSeparator()
    for (solution in solutions) {
        printLineWithPadding("Day ${solution.day}: ${solution.name}")
        printTreeSeparator()
        printLineWithPadding("I: ${solution.solvePartOne()} | II: ${solution.solvePartTwo()}")
        printTreeSeparator()
    }
}