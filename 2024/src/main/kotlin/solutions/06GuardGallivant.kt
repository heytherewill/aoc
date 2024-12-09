package com.heytherewill.solutions

import com.heytherewill.utilities.Degrees
import com.heytherewill.utilities.Direction
import com.heytherewill.utilities.Grid
import com.heytherewill.utilities.Point
import com.heytherewill.utilities.addToSetOfKey
import com.heytherewill.utilities.isInBounds
import com.heytherewill.utilities.itemAtPoint
import com.heytherewill.utilities.setItemAtPoint

private class State(val grid: Grid<Tile>, val startingPoint: Point)
private enum class Tile {
    Guard,
    Visited,
    Obstacle,
    Empty;

    override fun toString(): String =
        when(this) {
            Guard -> "^"
            Visited -> "X"
            Obstacle -> "#"
            Empty -> "."
        }
}

class GuardGallivant : Solution {
    override val name: String = "Guard Gallivant"

    override fun solvePartOne(input: String): Long {
        val state = parseAsState(input)
        state.grid.traverse(state.startingPoint)

        return state.grid.sumOf { lines ->
            lines.count { tile -> tile == Tile.Visited }
        }.toLong()
    }

    override fun solvePartTwo(input: String): Long {
        val state = parseAsState(input)
        val originalGrid = state.grid.copyOf()
        state.grid.traverse(state.startingPoint)

        val pointsToVerify = state.grid.indices.flatMap { y ->
            val line = state.grid[y]
            line.indices.mapNotNull { x ->
                val point = Point(x, y)
                if (state.grid.itemAtPoint(point) == Tile.Visited && point != state.startingPoint) point
                else null
            }
        }

        return pointsToVerify.count { pointToVerify ->
            originalGrid.copyOf().hasCyclesWithObstacleAt(
                newObstaclePoint = pointToVerify,
                startingPoint = state.startingPoint
            )
        }.toLong()
    }

    private fun parseAsState(input: String): State {
        val lines = input.lines()
        var startingPoint = Point(0, 0)
        val grid = lines.indices.map { y ->
            val line = lines[y]
            line.indices.map { x ->
                val char = lines[y][x]
                when (char) {
                    '#' -> Tile.Obstacle
                    '^' -> Tile.Guard.also { startingPoint = Point(x, y) }
                    else -> Tile.Empty
                }
            }.toTypedArray()
        }.toTypedArray()

        return State(grid, startingPoint)
    }

    private fun Grid<Tile>.traverse(startingPoint: Point) {
        var currentDirection = Direction.North
        var currentPoint = startingPoint

        do {
            val pointBeingChecked = currentPoint + currentDirection
            val tileBeingChecked = itemAtPoint(pointBeingChecked)
            when (tileBeingChecked) {
                Tile.Obstacle -> {
                    currentDirection += Degrees.Ninety
                }
                else -> {
                    setItemAtPoint(currentPoint, Tile.Visited)
                    currentPoint = pointBeingChecked
                }
            }
        } while (isInBounds(currentPoint))
    }

    private fun <T> Grid<T>.hasCyclesWithObstacleAt(
        newObstaclePoint: Point,
        startingPoint: Point
    ): Boolean {
        val visitedPointsWithDirections = HashMap<Point, HashSet<Direction>>()
        var currentDirection = Direction.North
        var currentPoint = startingPoint

        do {
            val pointBeingChecked = currentPoint + currentDirection
            val tileBeingChecked = itemAtPoint(pointBeingChecked)
            when (tileBeingChecked) {
                Tile.Obstacle -> {
                    currentDirection += Degrees.Ninety
                }
                else -> {

                    if (pointBeingChecked == newObstaclePoint) {
                        currentDirection += Degrees.Ninety
                    } else {
                        if (visitedPointsWithDirections[currentPoint]?.contains(currentDirection) == true) {
                            return true
                        }

                        visitedPointsWithDirections.addToSetOfKey(currentPoint, currentDirection)
                        currentPoint = pointBeingChecked
                    }
                }
            }
        } while (isInBounds(currentPoint))


        return false
    }
}