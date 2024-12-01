package com.heytherewill.utilities

// Dummy object so we can access the classLoader.
private object ResourceAccess

fun readFirstInputForDay(day: Int): String {
    return ResourceAccess::class.java.classLoader.getResource("$day-1.txt")!!.readText()
}

fun readSecondInputForDay(day: Int): String {
    return ResourceAccess::class.java.classLoader.getResource("$day-2.txt")!!.readText()
}