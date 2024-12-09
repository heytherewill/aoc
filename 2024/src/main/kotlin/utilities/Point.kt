package com.heytherewill.utilities

data class Point(val x: Int, val y: Int) {
    operator fun plus(other: Direction): Point = Point(x + other.x, y + other.y)
    operator fun plus(other: Point): Point = Point(x + other.x, y + other.y)
    operator fun minus(other: Point): Point = Point(x - other.x, y - other.y)
    fun distanceTo(other: Point) = Point(x - other.x, y - other.y)

    companion object {
        val zero = Point(0, 0)
    }
}