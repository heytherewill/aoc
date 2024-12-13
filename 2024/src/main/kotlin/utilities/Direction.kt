package com.heytherewill.utilities

enum class Direction(val x: Int, val y: Int) {
    North(0, -1),
    South(0, 1),
    East(1, 0),
    West(-1, 0),
    NorthEast(1, -1),
    NorthWest(-1, -1),
    SouthEast(1, 1),
    SouthWest(-1, 1);

    operator fun plus(other: Degrees): Direction =
        when (this) {
            North -> East
            South -> West
            East -> South
            West -> North
            NorthEast -> SouthEast
            NorthWest -> NorthEast
            SouthEast -> SouthWest
            SouthWest -> NorthWest
        }

    companion object {
        val cardinal = listOf(
            North,
            South,
            East,
            West
        )

        val ordinal = listOf(
            NorthEast,
            SouthWest,
            NorthWest,
            SouthEast
        )
    }

}

enum class Degrees {
    Ninety
}