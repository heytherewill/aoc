#include <stdlib.h>
#include <string.h>
#include "../utilities/file.h"
#include "../utilities/math.h"
#include "../utilities/string.h"
#include <search.h>
#include <ctype.h>
#include <stdbool.h>

static long extrapolate(const long *numbers, int numberCount, bool extrapolateBackwards) { // NOLINT(*-no-recursion)
    long *nextSequence = malloc((numberCount - 1) * sizeof(long));

    bool isAllZeroes = true;
    long previousNumber = numbers[0];
    for (int i = 1; i < numberCount; ++i) {
        long diff = numbers[i] - previousNumber;
        previousNumber = numbers[i];
        nextSequence[i - 1] = diff;

        isAllZeroes &= diff == 0;
    }

    long extrapolatedValue = isAllZeroes ? 0 : extrapolate(nextSequence, numberCount - 1, extrapolateBackwards);

    if (extrapolateBackwards) {
        return numbers[0] - extrapolatedValue;
    } else {
        return numbers[numberCount - 1] + extrapolatedValue;
    }
}

static long solve(bool extrapolateBackwards) {
    long sumOfNextValues = 0;
    readEveryLineForInput(9) {
        long *listOfNumbers = malloc(1000 * sizeof(long));
        int numberCount = 0;
        int indexOfCurrentLine = 0;

        do {
            if (!isdigit(currentLine[indexOfCurrentLine]) && currentLine[indexOfCurrentLine] != '-') {
                indexOfCurrentLine++;
            } else {
                long number = readNextSpaceSeparatedNumber(currentLine, &indexOfCurrentLine);
                listOfNumbers[numberCount++] = number;
            }

        } while (currentLine[indexOfCurrentLine] != '\n' && currentLine[indexOfCurrentLine] != '\0');

        long nextNumber = extrapolate(listOfNumbers, numberCount, extrapolateBackwards);
        sumOfNextValues += nextNumber;
    }
    fclose(filePointer);

    return sumOfNextValues;
}

long solve09Part1() {
    return solve(false);
}

long solve09Part2() {
    return solve(true);
}