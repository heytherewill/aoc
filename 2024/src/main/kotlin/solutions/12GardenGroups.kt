package com.heytherewill.solutions

import com.heytherewill.utilities.Direction
import com.heytherewill.utilities.Point
import com.heytherewill.utilities.forEachPoint
import com.heytherewill.utilities.itemAtPoint
import com.heytherewill.utilities.parseAsGrid
import java.util.*

private typealias Region = HashSet<Point>

class GardenGroups : Solution {
    override val name: String = "Garden Groups"

    override fun solvePartOne(input: String) =
        parseAsRegions(input)
            .sumOf { region -> region.area * region.perimeter }
            .toLong()

    override fun solvePartTwo(input: String): Long =
        parseAsRegions(input)
            .sumOf { region -> region.area * region.sides }
            .toLong()

    private fun parseAsRegions(input: String): List<Region> {
        val grid = parseAsGrid(input)
        val usedPlotPoints = HashSet<Point>()
        val regions = mutableListOf<Region>()
        grid.forEachPoint { point ->
            val plot = grid.itemAtPoint(point)
            if (usedPlotPoints.contains(point)) {
                return@forEachPoint
            }

            usedPlotPoints.add(point)
            val region = Region()
            region.add(point)

            val pointsOfInterest = ArrayDeque(Direction.cardinal.map { point + it })
            do {
                val candidatePoint = pointsOfInterest.pop()
                val candidatePlot = grid.itemAtPoint(candidatePoint)
                if (candidatePlot == plot && usedPlotPoints.contains(candidatePoint).not()) {
                    usedPlotPoints.add(candidatePoint)
                    region.add(candidatePoint)
                    pointsOfInterest.addAll(Direction.cardinal.map { candidatePoint + it })
                }

            } while (pointsOfInterest.isNotEmpty())

            regions.add(region)
        }

        return regions
    }

    private val Region.area: Int get() = size
    private val Region.perimeter: Int get() =
        sumOf { plot ->
            Direction.cardinal.count { direction ->
                contains(plot + direction).not()
            }
        }

    private val Region.sides: Int get() {
        val selectX: (Point) -> Int  = { it.x }
        val selectY: (Point) -> Int  = { it.y }
        val selectors = listOf(
            selectY to listOf(Direction.North, Direction.South) to selectX,
            selectX to listOf(Direction.East, Direction.West) to selectY
        )

        return selectors.sumOf { selector ->
            val lineOfPlots = groupBy(selector.first.first).toList()
            lineOfPlots.sumOf { plotGroup ->
                selector.first.second.sumOf { direction ->
                    val perpendicularSelector = selector.second
                    val outwardFacingPlots =
                        plotGroup.second
                            .filter { contains(it + direction).not() }
                            .sortedBy(perpendicularSelector)

                    outwardFacingPlots.indices.count { plotIndex ->
                        val plot = outwardFacingPlots[plotIndex]
                        val previousPlot = outwardFacingPlots.getOrNull(plotIndex - 1)
                        previousPlot?.let(perpendicularSelector) != perpendicularSelector(plot) - 1
                    }
                }
            }
        }
    }
}