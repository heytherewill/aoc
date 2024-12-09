package com.heytherewill.solutions

import com.heytherewill.utilities.Grid
import com.heytherewill.utilities.Point
import com.heytherewill.utilities.addToSetOfKey
import com.heytherewill.utilities.forEachPoint
import com.heytherewill.utilities.isInBounds
import com.heytherewill.utilities.itemAtPoint
import com.heytherewill.utilities.parseAsGrid
import com.heytherewill.utilities.print
import com.heytherewill.utilities.setItemAtPoint

class ResonantCollinearity : Solution {
    override val name = "Resonant Collinearity"

    override fun solvePartOne(input: String): Long {
        val grid = parseAsGrid(input)
        val antinodes = HashSet<Point>()

        for (antennaPoints in grid.getAntennaPositions()) {
            for (pointOne in antennaPoints) {
                for (pointTwo in antennaPoints) {
                    val distance = pointOne.distanceTo(pointTwo)
                    if (distance != Point.zero) {
                        val antinodeLocation = pointOne + distance
                        if (grid.isInBounds(antinodeLocation)) {
                            antinodes.add(antinodeLocation)
                        }
                    }
                }
            }
        }

        return antinodes.size.toLong()
    }

    override fun solvePartTwo(input: String): Long {
        val grid = parseAsGrid(input)
        val antinodes = HashSet<Point>()

        for (antennaPoints in grid.getAntennaPositions()) {
            for (pointOne in antennaPoints) {
                antinodes.add(pointOne)
                for (pointTwo in antennaPoints) {
                    val distance = pointOne.distanceTo(pointTwo)
                    if (distance == Point.zero) continue

                    var currentPoint = pointOne + distance
                    while (grid.isInBounds(currentPoint)) {
                        antinodes.add(currentPoint)
                        currentPoint += distance
                    }
                }
            }
        }

        return antinodes.size.toLong()
    }

    private fun Grid<Char>.getAntennaPositions(): List<HashSet<Point>> {
        val antennaPositions = HashMap<Char, HashSet<Point>>()

        forEachPoint { point ->
            val item = itemAtPoint(point)
            when (item) {
                '.', null -> Unit
                else -> antennaPositions.addToSetOfKey(item, point)
            }
        }

        return antennaPositions.map { it.value }.toList()
    }
}