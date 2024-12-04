package com.heytherewill.solutions

import com.heytherewill.utilities.readFirstInputForDay
import com.heytherewill.utilities.readSecondInputForDay

class CeresSearch : Solution {
    override val day = 4
    override val name = "Ceres Search"


    override fun solvePartOne(): Long {
        return 0
        val input = readFirstInputForDay(day)
        val matrix = parseAsMatrix(input)
        val matchesNeeded = listOf('X', 'M', 'A', 'S')

        val numberOfMatches = matrix.indices.sumOf { y ->
            val line = matrix[y]
            line.indices.sumOf { x ->
                val character = line[x]
                if (character == matchesNeeded[0]) {
                    Direction.entries.sumOf { direction ->
                        verifyWord(matrix, x, y, direction, 1, matchesNeeded)
                    }
                } else {
                    0
                }
            }
        }

        return numberOfMatches.toLong()
    }

    override fun solvePartTwo(): Long {
        val input = readSecondInputForDay(day)
        val matrix = parseAsMatrix(input)
        val matchesNeeded = listOf('M', 'A', 'S')
        val relevantDirections = listOf(Direction.NorthEast, Direction.SouthEast, Direction.NorthWest, Direction.NorthWest)
        val skips = mutableListOf<Pair<Int, Int>>()

        val numberOfMatches = matrix.indices.sumOf { y ->
            val line = matrix[y]
            line.indices.sumOf { x ->
                val character = line[x]
                if (character == matchesNeeded[0]) {
                    relevantDirections.sumOf { direction ->
                        val match = verifyWord(matrix, x, y, direction, 1, matchesNeeded)
                        if (match == 1) {
                            val (ignoreTile, crossingDirection) = when (direction) {
                                Direction.NorthEast -> x to y - 2 to Direction.SouthEast
                                Direction.SouthEast -> x to y + 2 to Direction.NorthEast
                                Direction.NorthWest -> x - 2 to y to Direction.SouthWest
                                Direction.SouthWest -> x + 2 to y to Direction.NorthWest
                                else -> throw IllegalStateException()
                            }

                            if (matrix[ignoreTile.second][ignoreTile.first] == matchesNeeded[0]) {
                                verifyWord(matrix, ignoreTile.first, ignoreTile.second, crossingDirection, 1, matchesNeeded).also { isXmas ->
                                    if (isXmas == 1) {
                                        skips.add(ignoreTile)
                                    }
                                }
                            } else {
                                0
                            }

                        } else {
                            0
                        }
                    }
                } else {
                    0
                }
            }
        }

        return numberOfMatches.toLong()
    }

    private fun verifyWord(matrix: List<List<Char>>, currentX: Int, currentY: Int, direction: Direction, currentMatch: Int, matchesNeeded: List<Char>): Int {

        val x = currentX + direction.x
        val width = matrix.first().size
        if (x < 0 || x >= width) {
            return 0
        }

        val y = currentY + direction.y
        val height = matrix.size
        if (y < 0 || y >= height) {
            return 0
        }

        return if (matrix[y][x] != matchesNeeded[currentMatch]) { 0 }
        else if (currentMatch == matchesNeeded.size - 1) { 1 }
        else {
            verifyWord(matrix, x, y, direction, currentMatch + 1, matchesNeeded)
        }
    }

    private fun parseAsMatrix(input: String): List<List<Char>> =
        input.lines().map { it.toList() }

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