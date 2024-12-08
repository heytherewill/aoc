package com.heytherewill.solutions

import java.util.Comparator

private typealias OrderingRules = HashMap<Int, HashSet<Int>>

class PrintQueue : Solution {
    override val name = "Print Queue"

    data class SafetyManual(
        val orderingRules: OrderingRuleComparator,
        val pagesToProduce: List<List<Int>>
    )

    override fun solvePartOne(input: String): Long {
        val instructions = parseAsSafetyManual(input)

        return instructions.pagesToProduce
            .filter { list -> list.isAlreadyOrdered(instructions.orderingRules) }
            .sumOf { list -> list[list.size / 2] }
            .toLong()
    }

    override fun solvePartTwo(input: String): Long {
        val instructions = parseAsSafetyManual(input)

        return instructions.pagesToProduce
            .filter { list -> !list.isAlreadyOrdered(instructions.orderingRules) }
            .map { list -> list.sortedWith(instructions.orderingRules) }
            .sumOf { list -> list[list.size / 2] }
            .toLong()
    }

    private fun List<Int>.isAlreadyOrdered(comparator: Comparator<Int>): Boolean {
        val sortedList = this.sortedWith(comparator)
        return this == sortedList
    }

    private fun parseAsSafetyManual(input: String): SafetyManual {
        val orderingRules = OrderingRules()
        val pagesToProduce = mutableListOf<List<Int>>()
        var readingRules = true
        for (line in input.lines()) {
            if (line.isEmpty()) {
                readingRules = false
            } else if (readingRules) {
                val elements = line.split("|")
                orderingRules.addToSetOfKey(
                    key = elements.first().toInt(),
                    value = elements.last().toInt()
                )
            } else {
                pagesToProduce.add(
                    line.split(",").map { it.toInt() }
                )
            }
        }

        return SafetyManual(OrderingRuleComparator(orderingRules), pagesToProduce)
    }

    private fun OrderingRules.addToSetOfKey(key: Int, value: Int) {
        if (!containsKey(key)) {
            this[key] = HashSet()
        }

        this[key]!!.add(value)
    }
}

class OrderingRuleComparator(
    private val orderingRules: OrderingRules
) : Comparator<Int> {
    override fun compare(o1: Int, o2: Int): Int {
        val rules = orderingRules[o1]
        if (rules?.contains(o2) == true) return -1

        val secondRules = orderingRules[o2]
        if (secondRules?.contains(o1) == true) return 1

        return 0
    }
}
