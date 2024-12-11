package com.heytherewill.solutions

private data class Equation(
    val expectedOutput: Long,
    val arguments: List<Int>
)

class BridgeRepair(useCache: Boolean) : SlowRunningSolution(useCache) {
    override val name: String = "Bridge Repair"

    override fun slowSolvePartOne(input: String) =
        parseAsEquations(input)
            .filter(::canBeEvaluated)
            .sumOf { it.expectedOutput }

    override fun slowSolvePartTwo(input: String)=
        parseAsEquations(input)
            .filter { canBeEvaluated(it, validOperations = Operation.entries) }
            .sumOf { it.expectedOutput }

    private fun parseAsEquations(input: String): List<Equation> =
        input.lines().map { line ->
            val parts = line.split(":")
            val expectedOutput = parts.first().toLong()
            val arguments = parts.last().trim().split(" ").map { it.toInt() }
            Equation(
                expectedOutput = expectedOutput,
                arguments = arguments
            )
        }

    private fun canBeEvaluated(
        equation: Equation,
        currentSum: Long = 0,
        currentArgumentIndex: Int = 0,
        operation: Operation = Operation.Addition,
        validOperations: List<Operation> = listOf(Operation.Addition, Operation.Multiplication)
    ): Boolean {
        val currentArgument = equation.arguments[currentArgumentIndex]
        val newSum = when (operation) {
            Operation.Addition -> currentSum + currentArgument
            Operation.Multiplication -> currentSum * currentArgument
            Operation.Concatenation -> "$currentSum$currentArgument".toLong()
        }

        val nextArgumentIndex = currentArgumentIndex + 1
        return if (nextArgumentIndex == equation.arguments.size) {
            newSum == equation.expectedOutput
        } else {
            validOperations.any { nextOperation ->
                canBeEvaluated(equation, newSum, nextArgumentIndex, nextOperation, validOperations)
            }
        }
    }

    enum class Operation { Addition, Multiplication, Concatenation }
}