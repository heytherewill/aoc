package com.heytherewill

import com.heytherewill.solutions.BridgeRepair
import com.heytherewill.solutions.CeresSearch
import com.heytherewill.solutions.DiskFragmenter
import com.heytherewill.solutions.GuardGallivant
import com.heytherewill.solutions.HistorianHysteria
import com.heytherewill.solutions.MullItOver
import com.heytherewill.solutions.PrintQueue
import com.heytherewill.solutions.RedNosedReports
import com.heytherewill.solutions.ResonantCollinearity
import com.heytherewill.utilities.readFirstInputForDay
import com.heytherewill.utilities.readSecondInputForDay

private val solutions = listOf(
    HistorianHysteria(),
    RedNosedReports(),
    MullItOver(),
    CeresSearch(),
    PrintQueue(),
    GuardGallivant(),
    BridgeRepair(),
    ResonantCollinearity(),
    DiskFragmenter()
)

private const val lineInternalSpace = 39
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

    print("                    -                    \n")
    print("                   ---                   \n")
    print("                 --*----                 \n")
    print("               -------*---               \n")
    print("             ------*---*----             \n")
    print("           ---O----------O----           \n")
    print("         -------*---O-----*-----         \n")
    print("       ----O-----*------*---------       \n")
    print("     ---------O------*-----------*--     \n")
    print("   ------*--------*---------0---------   \n")
    print("  ----------O---------0--------*-------  \n")
    print(" -----------O---------0--------*-------- \n")
    printTreeSeparator()
    printLineWithPadding("Advent of Code 2024")
    printTreeSeparator()
    for (solutionIndex in solutions.indices) {
        val day = solutionIndex + 1
        val solution = solutions[solutionIndex]
        printLineWithPadding("Day $day: ${solution.name}")
        printTreeSeparator()
        val partOneInput = readFirstInputForDay(day)
        val partTwoInput = readSecondInputForDay(day)
        printLineWithPadding("I: ${solution.solvePartOne(partOneInput)} | II: ${solution.solvePartTwo(partTwoInput)}")
        printTreeSeparator()
    }
}