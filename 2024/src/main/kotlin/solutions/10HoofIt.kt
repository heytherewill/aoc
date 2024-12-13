package com.heytherewill.solutions

import com.heytherewill.utilities.Direction
import com.heytherewill.utilities.Grid
import com.heytherewill.utilities.Point
import com.heytherewill.utilities.forEachPoint
import com.heytherewill.utilities.itemAtPoint
import com.heytherewill.utilities.parseAsIntegerGrid

class HoofIt : Solution {
    override val name = "Hoof It"

    override fun solvePartOne(input: String): Long {
        val trailHeadEndings = findTrailHeadEndings(input)
        return trailHeadEndings.values
            .sumOf { validEndpoints -> validEndpoints.distinct().count() }
            .toLong()
    }

    override fun solvePartTwo(input: String): Long {
        val trailHeadEndings = findTrailHeadEndings(input)
        return trailHeadEndings.values
            .sumOf { validEndpoints -> validEndpoints.count() }
            .toLong()
    }

    private fun findTrailHeadEndings(input: String) : HashMap<Point, List<Point>> {
        val grid = parseAsIntegerGrid(input)
        val trailHeadEndings = HashMap<Point, List<Point>>()
        grid.forEachPoint { point ->
            val elevation = grid.itemAtPoint(point) ?: return@forEachPoint
            if (elevation == 0) {
                val endings = findEndPointsForTrailHead(point, grid)
                trailHeadEndings[point] = endings
            }
        }

        return trailHeadEndings
    }

    private fun findEndPointsForTrailHead(
        currentPoint: Point,
        grid: Grid<Int>,
        currentElevation: Int = 0
    ): List<Point> {
        val pointIsValidElevation = grid.itemAtPoint(currentPoint) == currentElevation
        return if (pointIsValidElevation) {
            if (currentElevation == 9) listOf(currentPoint)
            else Direction.cardinal
                .map { direction -> findEndPointsForTrailHead(currentPoint + direction, grid, currentElevation + 1) }
                .reduce { a, b -> a + b }
        } else {
            emptyList()
        }
    }
}