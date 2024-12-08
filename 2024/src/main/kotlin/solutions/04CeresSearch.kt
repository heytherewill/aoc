package com.heytherewill.solutions

import com.heytherewill.utilities.readFirstInputForDay
import com.heytherewill.utilities.readSecondInputForDay

private typealias Matrix = List<List<Char>>

class CeresSearch : Solution {
    override val day = 4
    override val name = "Ceres Search"


    override fun solvePartOne(): Long {
        val input = readFirstInputForDay(day)
        val matrix = parseAsMatrix(input)
        val matchesNeeded = listOf('X', 'M', 'A', 'S')

        val numberOfMatches = matrix.indices.sumOf { y ->
            val line = matrix[y]
            line.indices.sumOf { x ->
                val point = Point(x, y)
                Direction.entries.sumOf { direction ->
                     matrix.verifyWord(point, direction, 0, matchesNeeded)
                }
            }
        }

        return numberOfMatches.toLong()
    }

    override fun solvePartTwo(): Long {
        val input = readSecondInputForDay(day)
        val matrix = parseAsMatrix(input)

        val validCrosses: List<List<Pair<Direction, Char>>> = listOf(
            listOf(
                Direction.NorthWest to 'M',
                Direction.NorthEast to 'M',
                Direction.SouthEast to 'S',
                Direction.SouthWest to 'S'
            ),
            listOf(
                Direction.NorthEast to 'M',
                Direction.SouthEast to 'M',
                Direction.SouthWest to 'S',
                Direction.NorthWest to 'S'
            ),

            listOf(
                Direction.SouthEast to 'M',
                Direction.SouthWest to 'M',
                Direction.NorthWest to 'S',
                Direction.NorthEast to 'S'
            ),

            listOf(
                Direction.SouthWest to 'M',
                Direction.NorthWest to 'M',
                Direction.NorthEast to 'S',
                Direction.SouthEast to 'S'
            ),
        )

        return matrix.indices.sumOf { y ->
            val line = matrix[y]
            line.indices.sumOf { x ->
                val point = Point(x, y)
                if (matrix.safeCheckIndex(point, 'A')) {
                    val found = validCrosses.any { matchPairs ->
                        matchPairs.all {  matchPair ->
                            matrix.safeCheckIndex(point + matchPair.first, matchPair.second)
                        }
                    }
                    if (found) {
                        1L
                    } else {
                        0L
                    }
                } else {
                    0L
                }
            }
        }
    }

    private fun Matrix.verifyWord(
        currentPoint: Point,
        direction: Direction,
        currentMatch: Int,
        matchesNeeded: List<Char>
    ): Int =
        if (!safeCheckIndex(currentPoint, matchesNeeded[currentMatch])) { 0 }
        else if (currentMatch == matchesNeeded.size - 1) { 1 }
        else {
            verifyWord(currentPoint + direction, direction, currentMatch + 1, matchesNeeded)
        }

    private fun Matrix.safeCheckIndex(point: Point, char: Char): Boolean {
        val width = first().size
        if (point.x < 0 || point.x >= width) {
            return false
        }

        val height = size
        if (point.y < 0 || point.y >= height) {
            return false
        }

        return this[point.y][point.x] == char
    }

    private fun parseAsMatrix(input: String): Matrix =
        input.lines().map { it.toList() }

    private data class Point(val x: Int, val y: Int) {
        operator fun plus(other: Direction): Point = Point(x + other.x, y + other.y)
    }

    private enum class Direction(val x: Int, val y: Int) {
        North(0, -1),
        South(0, 1),
        East(1, 0),
        West(-1, 0),
        NorthEast(1, -1),
        NorthWest(-1, -1),
        SouthEast(1, 1),
        SouthWest(-1, 1);
    }
}