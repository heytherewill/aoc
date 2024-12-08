package com.heytherewill.solutions

interface Solution {
    val name: String
    fun solvePartOne(input: String): Long
    fun solvePartTwo(input: String): Long
}