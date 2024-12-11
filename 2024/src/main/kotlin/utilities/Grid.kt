package com.heytherewill.utilities

typealias Grid<T> = Array<Array<T>>

fun parseAsGrid(input: String): Grid<Char> =
    input.lines().map { line -> line.toList().toTypedArray() }.toTypedArray()

fun parseAsIntegerGrid(input: String): Grid<Int> =
    input.lines().map { line -> line.map { it.digitToInt() }.toTypedArray() }.toTypedArray()

fun <T> Grid<T>.forEachPoint(fn: (Point) -> Unit) {
    for (y in indices) {
        val line = this[y]
        for (x in line.indices) {
            fn(Point(x, y))
        }
    }
}

fun <T> Grid<T>.itemAtPoint(point: Point): T? =
    if (isInBounds(point)) this[point.y][point.x] else null

fun <T> Grid<T>.setItemAtPoint(point: Point, value: T) {
    this[point.y][point.x] = value
}

fun <T> Grid<T>.isInBounds(point: Point): Boolean {
    val width = first().size
    if (point.x < 0 || point.x >= width) {
        return false
    }

    val height = size
    if (point.y < 0 || point.y >= height) {
        return false
    }

    return true
}

fun <T> Grid<T>.print() {
    for (y in this) {
        for (x in y) {
            print(x)
        }
        println()
    }
}