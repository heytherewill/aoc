package com.heytherewill.solutions

import com.heytherewill.utilities.Direction
import com.heytherewill.utilities.Grid
import com.heytherewill.utilities.Point
import com.heytherewill.utilities.itemAtPoint

class CeresSearch : Solution {
    override val name = "Ceres Search"

    override fun solvePartOne(input: String): Long {
        val matrix = parseAsGrid(input)
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

    override fun solvePartTwo(input: String): Long {
        val matrix = parseAsGrid(input)

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
                if (matrix.itemAtPoint(point) == 'A') {
                    val found = validCrosses.any { matchPairs ->
                        matchPairs.all {  matchPair ->
                            matrix.itemAtPoint(point + matchPair.first) == matchPair.second
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

    private fun Grid<Char>.verifyWord(
        currentPoint: Point,
        direction: Direction,
        currentMatch: Int,
        matchesNeeded: List<Char>
    ): Int =
        if (itemAtPoint(currentPoint) != matchesNeeded[currentMatch]) { 0 }
        else if (currentMatch == matchesNeeded.size - 1) { 1 }
        else {
            verifyWord(currentPoint + direction, direction, currentMatch + 1, matchesNeeded)
        }


    private fun parseAsGrid(input: String): Grid<Char> =
        input.lines().map{ line -> line.toList().toTypedArray() }.toTypedArray()
}