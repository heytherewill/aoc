package com.heytherewill.solutions

class MullItOver : Solution {
    override val name = "Mull It Over"

    override fun solvePartOne(input: String): Long {
        val sum = processCorruptedProgramMemory(input, useConditionals = false)
        return sum
    }


    override fun solvePartTwo(input: String): Long {
        val sum = processCorruptedProgramMemory(input, useConditionals = true)
        return sum
    }
    private fun processCorruptedProgramMemory(input: String, useConditionals: Boolean): Long {
        var sum = 0L
        var index = 0
        var enabled = true
        do {
            if (input[index] == 'm' && input[index+1] == 'u' && input[index+2] == 'l' && input[index+3] == '(') {
                index+=4
                val firstNumber = StringBuilder()
                while (input[index].isDigit()) {
                    firstNumber.append(input[index++])
                }

                if (firstNumber.isNotEmpty() && input[index] == ',') {
                    index++

                    val secondNumber = StringBuilder()
                    while (input[index].isDigit()) {
                        secondNumber.append(input[index++])
                    }
                    if (secondNumber.isNotEmpty() && input[index] == ')') {
                        index++

                        if (enabled) {
                            sum += firstNumber.toString().toInt() * secondNumber.toString().toInt()
                        }
                    }
                }
            } else if (useConditionals && input[index] == 'd' && input[index+1] == 'o') {
                index+=2
                if (input[index] == '(' && input[index+1] == ')') {
                    index+=2
                    enabled = true
                } else if (input[index] == 'n' && input[index+1] == '\''&& input[index+2] == 't'&& input[index+3] == '('&& input[index+4] == ')') {
                    index += 5
                    enabled = false
                }

            } else {
                index++
            }
        } while (input.length > index)

        return sum
    }
}