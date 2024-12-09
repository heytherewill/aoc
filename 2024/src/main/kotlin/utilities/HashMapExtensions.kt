package com.heytherewill.utilities

fun <T, R> HashMap<T, HashSet<R>>.addToSetOfKey(key: T, value: R) {
    if (!containsKey(key)) {
        this[key] = HashSet()
    }

    this[key]!!.add(value)
}