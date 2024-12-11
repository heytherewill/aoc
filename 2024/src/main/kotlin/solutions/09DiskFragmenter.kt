package com.heytherewill.solutions

import kotlin.math.min

private sealed interface DiskEntry {
    val blocks: Long

    data class File(val id: Long, override val blocks: Long, val alreadyMoved: Boolean = false) : DiskEntry
    data class EmptySpace(override val blocks: Long) : DiskEntry
}

class DiskFragmenter(useCache: Boolean) : SlowRunningSolution(useCache) {
    override val name = "Disk Fragmenter"

    override fun slowSolvePartOne(input: String): Long {
        val fullDiskMap = decompress(input)
        val fragmentedDiskMap = mutableListOf<DiskEntry.File>()

        var increasingPointer = 0
        var decreasingPointer = fullDiskMap.size - 1

        do {
            when (val entry = fullDiskMap[increasingPointer++]) {
                is DiskEntry.EmptySpace -> {
                    var spaceToClear = entry.blocks
                    do {
                        val candidate = fullDiskMap[decreasingPointer]
                        if (candidate is DiskEntry.File) {
                            if (candidate.blocks > spaceToClear) {
                                fullDiskMap[decreasingPointer] =
                                    candidate.copy(blocks = candidate.blocks - spaceToClear)
                                fragmentedDiskMap.add(DiskEntry.File(id = candidate.id, blocks = spaceToClear))
                                spaceToClear = 0
                            } else {
                                fragmentedDiskMap.add(candidate)
                                spaceToClear -= candidate.blocks
                                decreasingPointer--
                            }
                        } else {
                            decreasingPointer--
                        }

                    } while (spaceToClear > 0)
                }

                is DiskEntry.File -> {
                    fragmentedDiskMap.add(entry)
                }
            }

        } while (increasingPointer < decreasingPointer)

        var position = 0L
        return fragmentedDiskMap.sumOf { file ->
            (0 until file.blocks).sumOf { i ->
                (position + i) * file.id
            }.also {
                position += file.blocks
            }
        }
    }

    override fun slowSolvePartTwo(input: String): Long {
        val fullDiskMap = decompress(input).toMutableList()

        var decreasingPointer = fullDiskMap.size - 1
        do {
            when (val candidateToMove = fullDiskMap[decreasingPointer--]) {
                is DiskEntry.File -> {
                    if (candidateToMove.alreadyMoved)
                        continue

                    var innerEmptySpaceSearchIndex = 0
                    var moved = false
                    do {
                        val candidateEmptySpace = fullDiskMap[innerEmptySpaceSearchIndex]
                        if (candidateEmptySpace is DiskEntry.EmptySpace) {
                            if (candidateEmptySpace.blocks >= candidateToMove.blocks) {
                                fullDiskMap[decreasingPointer+1] = DiskEntry.EmptySpace(candidateToMove.blocks)
                                fullDiskMap.add(innerEmptySpaceSearchIndex, candidateToMove.copy(alreadyMoved = true))

                                if (candidateEmptySpace.blocks > candidateToMove.blocks) {
                                    fullDiskMap[innerEmptySpaceSearchIndex + 1] = candidateEmptySpace.copy(blocks = candidateEmptySpace.blocks - candidateToMove.blocks)
                                    decreasingPointer++
                                } else {
                                    fullDiskMap.removeAt(innerEmptySpaceSearchIndex + 1)
                                }
                                moved = true
                            } else {
                                innerEmptySpaceSearchIndex++
                            }
                        } else {
                            innerEmptySpaceSearchIndex++
                        }

                    } while (!moved && innerEmptySpaceSearchIndex <= decreasingPointer)
                }

                is DiskEntry.EmptySpace -> Unit
            }
        } while (decreasingPointer >= 0)

        var position = 0L
        return fullDiskMap.sumOf { entry ->
            when (entry) {
                is DiskEntry.EmptySpace -> {
                    position += entry.blocks
                    0
                }
                is DiskEntry.File -> {

                    (0 until entry.blocks).sumOf { i ->
                        (position + i) * entry.id
                    }.also {
                        position += entry.blocks
                    }
                }
            }
        }
    }

    private fun decompress(input: String): Array<DiskEntry> {
        val builder = mutableListOf<DiskEntry>()
        var id = 0L
        var readingFile = false
        for (char in input) {
            readingFile = !readingFile
            val blockCount = char.digitToInt().toLong()
            if (blockCount == 0L)
                continue

            builder.add(
                if (readingFile) DiskEntry.File(id++, blockCount)
                else DiskEntry.EmptySpace(blockCount)
            )
        }

        return builder.toTypedArray()
    }
}