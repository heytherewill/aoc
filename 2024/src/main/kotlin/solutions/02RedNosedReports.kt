package com.heytherewill.solutions

import kotlin.math.abs

class RedNosedReports : Solution {
    override val name = "Red-Nosed Reports"
    private val safetyThreshold = 3

    override fun solvePartOne(input: String) =
        solve(input, problemDampenerIsActive = false)

    override fun solvePartTwo(input: String) =
        solve(input, problemDampenerIsActive = true)

    private fun solve(input: String, problemDampenerIsActive: Boolean): Long {
        val reports = parseAsReports(input)
        return reports.count { report ->
            val firstViolatingIndex = findFirstViolatingIndex(report) ?: return@count true

            if (problemDampenerIsActive) {
                val problemIsFixable =
                    // Check for the first and second items and the items around the problematic level.
                    findFirstViolatingIndex(report.indices.drop(1).map { report[it] }) == null ||
                    findFirstViolatingIndex(report.indices.filter { it != 1 }.map { report[it] }) == null ||
                    findFirstViolatingIndex(report.indices.filter { it != firstViolatingIndex - 1 }.map { report[it] }) == null ||
                    findFirstViolatingIndex(report.indices.filter { it != firstViolatingIndex }.map { report[it] }) == null ||
                    findFirstViolatingIndex(report.indices.filter { it != firstViolatingIndex + 1 }.map { report[it] }) == null
                if (problemIsFixable) {
                    return@count true
                }
            }

            return@count false
        }.toLong()
    }

    private fun findFirstViolatingIndex(report: List<Long>): Int? {
        val trend = report[0] < report[1]
        for (levelIndex in report.indices.drop(1)) {
            val previous = report[levelIndex - 1]
            val current = report[levelIndex]
            val isIncreasing = previous < current
            val difference = abs(current - previous)
            if (trend != isIncreasing || difference < 1 || difference > safetyThreshold) {
                return levelIndex
            }
        }

        return null
    }

    private fun parseAsReports(input: String) : List<List<Long>> =
        input.lines().map { line ->
            line.split(" ").map { it.toLong() }
        }
}