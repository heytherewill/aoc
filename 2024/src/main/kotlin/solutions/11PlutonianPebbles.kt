package com.heytherewill.solutions

class PlutonianPebbles : Solution {

    override val name = "Plutonian Pebbles"

    override fun solvePartOne(input: String): Long {
        val stones = input.split(" ").map { it.toLong() }.toMutableList()
        return stones.sumOf { blink(it, 25) }
    }

    override fun solvePartTwo(input: String): Long {
        val stones = input.split(" ").map { it.toLong() }.toMutableList()
        var stoneCount = 0
        return stones.sumOf { blink(it, 75) }
    }

    private val cache = HashMap<Pair<Long, Int>, Long>()
    private fun blink(stone: Long, numberOfBlinks: Int): Long {
        val key = stone to numberOfBlinks
        return cache.getOrElse(key) {
            val result = when {
                numberOfBlinks == 0 -> 1L
                stone == 0L -> blink(1, numberOfBlinks - 1)
                stone.toString().length % 2 == 0 -> {
                    val stoneString = stone.toString()
                    val sizeOfSplit = stoneString.length / 2
                    val firstStoneNumber = stoneString.take(sizeOfSplit).toLong()
                    val secondStoneNumber = stoneString.drop(sizeOfSplit).toLong()
                    blink(firstStoneNumber, numberOfBlinks - 1) +
                            blink(secondStoneNumber, numberOfBlinks - 1)
                }
                else -> blink(stone * 2024, numberOfBlinks - 1)
            }

            cache[key] = result
            result
        }
    }
}