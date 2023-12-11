#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../utilities/utilities.h"

typedef struct Insertion {
    unsigned long indexInString;
    int numberToInsert;
} Insertion;

static const char *possibleDigits[9] = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};

static char *replaceWrittenDigitsOn(char *line) {

    int currentSubstitution = 0;
    const int maxNumberOfSubstitutions = 10;
    Insertion substitutions[maxNumberOfSubstitutions];
    for (int i = 0; i < maxNumberOfSubstitutions; i++) {
        substitutions[i].indexInString = -1;
    }

    for (int i = 0; i < 9; i++) {
        unsigned long startingIndex = 0;
        unsigned long indexOfThisDigit;
        do {
            indexOfThisDigit = indexOf(line, possibleDigits[i], startingIndex);
            if (indexOfThisDigit != -1) {
                Insertion newInsertion = { indexOfThisDigit, i + 1 };
                substitutions[currentSubstitution++] = newInsertion;
                startingIndex = indexOfThisDigit + strlen(possibleDigits[i]);
            }
        } while (indexOfThisDigit != -1);
    }


    currentSubstitution = 0;
    while (substitutions[currentSubstitution].indexInString != -1) {
        char spelledOutDigit[2];
        sprintf(spelledOutDigit, "%d", substitutions[currentSubstitution].numberToInsert);
        spelledOutDigit[1] = '\0';

        line = insertStringInIndex(line, spelledOutDigit, substitutions[currentSubstitution].indexInString + currentSubstitution);
        currentSubstitution++;
    }

    return line;
}

static long solve(bool replaceWrittenDigits) {
    long count = 0;

    readEveryLineForInput(1) {
        if (replaceWrittenDigits) {
            currentLine = replaceWrittenDigitsOn(currentLine);
        }

        char *numberString = malloc(3);
        numberString[2] = '\0';
        bool firstDigitWasFound = false;

        unsigned long numberOfCharsInLine = strlen(currentLine);
        for (int i = 0; i < numberOfCharsInLine; i++) {
            char character = currentLine[i];
            if (isdigit(character)) {
                if (!firstDigitWasFound) {
                    numberString[0] = character;
                    numberString[1] = character;
                    firstDigitWasFound = true;
                } else {
                    numberString[1] = character;
                }
            }
        }

        count += parseLong(numberString);
    }

    fclose(filePointer);

    return count;
}

long solve01Part1() {
    return solve(false);
}

long solve01Part2() {
    return solve(true);
}