package com.heytherewill.solutions

interface Solution {
    val day: Int
    val name: String
    fun solvePartOne(): Long
    fun solvePartTwo(): Long
}