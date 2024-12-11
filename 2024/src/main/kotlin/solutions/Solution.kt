package com.heytherewill.solutions

import com.heytherewill.utilities.readCachedSolution
import com.heytherewill.utilities.writeCachedSolution

interface Solution {
    val name: String
    fun solvePartOne(input: String): Long
    fun solvePartTwo(input: String): Long
}

abstract class SlowRunningSolution(
    private val useCache: Boolean
) : Solution {
    final override fun solvePartOne(input: String): Long {
        val fileName = name.toFileName()
        val cachedResult =
            if (useCache) {
                readCachedSolution(fileName, 1)
            } else {
                null
            }

        val result = cachedResult ?: slowSolvePartOne(input)
        writeCachedSolution(fileName, 1, result)
        return result
    }

    final override fun solvePartTwo(input: String): Long {
        val fileName = name.toFileName()
        val cachedResult =
            if (useCache) {
                readCachedSolution(fileName, 2)
            } else {
                null
            }

        val result = cachedResult ?: slowSolvePartTwo(input)
        writeCachedSolution(fileName, 2, result)
        return result
    }

    protected abstract fun slowSolvePartOne(input: String): Long
    protected abstract fun slowSolvePartTwo(input: String): Long

    private fun String.toFileName() = this.lowercase().replace(" ", "_")
}