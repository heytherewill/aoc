package com.heytherewill.utilities

import java.io.File
import java.nio.file.Paths

// Dummy object so we can access the classLoader.
private object ResourceAccess

private val root = Paths.get("").toAbsolutePath().toString()
private val solutionFolder = File("$root/.solution_cache/")

fun readFirstInputForDay(day: Int): String {
    return ResourceAccess::class.java.classLoader.getResource("$day-1.txt")!!.readText()
}

fun readSecondInputForDay(day: Int): String {
    return ResourceAccess::class.java.classLoader.getResource("$day-2.txt")!!.readText()
}

fun readCachedSolution(fileName: String, part: Int): Long? {
    val file = File("$root/.solution_cache/$fileName-$part.txt")
    return if (file.exists()) file.readText().toLong() else null
}

fun writeCachedSolution(fileName: String, part: Int, solution: Long) {
    solutionFolder.mkdirs()
    val file = File("$root/.solution_cache/$fileName-$part.txt")
    file.writeText(solution.toString())
}
