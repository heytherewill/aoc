package com.heytherewill.utilities

data class Point(val x: Int, val y: Int) {
    operator fun plus(other: Direction): Point = Point(x + other.x, y + other.y)
}