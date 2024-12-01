package com.heytherewill.solutions

import com.heytherewill.utilities.readFirstInputForDay
import com.heytherewill.utilities.readSecondInputForDay
import kotlin.math.abs

class HistorianHysteria : Solution {
    override val day = 1
    override val name = "Historian Hysteria"

    override fun solvePartOne(): Long {
        val input = readFirstInputForDay(1)
        val (listOne, listTwo) = parseListsFromInput(input)

        return listOne.sorted()
            .zip(listTwo.sorted())
            .sumOf { (first, second) -> abs(first - second) }
    }

    override fun solvePartTwo(): Long {
        val input = readSecondInputForDay(1)
        val (listOne, listTwo) = parseListsFromInput(input)

        return listOne.sumOf { first ->
            first * listTwo.count { second -> first == second }
        }
    }

    private fun parseListsFromInput(input: String): Pair<List<Long>, List<Long>> {
        val listOne = mutableListOf<Long>()
        val listTwo = mutableListOf<Long>()

        for (line in input.lines()) {
            val number = line.split("   ")
            listOne.add(number.first().toLong())
            listTwo.add(number.last().toLong())
        }

        return listOne to listTwo
    }
}