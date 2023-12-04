#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../utilities/file.h"
#include "../utilities/string.h"
#include "../utilities/math.h"

typedef struct Index {
    long row;
    long column;
} Index;

typedef struct NeighbouringIndexes {
    Index* indexes;
    int foundIndexes;
} NeighbouringIndexes;

NeighbouringIndexes findNeighbouringIndexes(
    int row,
    int column,
    unsigned long numberOfRows,
    unsigned long numberOfColumns,
    int numberOfDigitsForCurrentPart
) {

    bool checkRowAbove = row != 0;
    bool checkRowBelow = row != numberOfRows;
    bool checkCharacterBefore = (column - numberOfDigitsForCurrentPart) != 0;
    bool checkCharacterAfter = column != numberOfColumns;

    int totalNumberOfIndexesToCheck =
            (checkRowAbove * numberOfDigitsForCurrentPart) +
            (checkRowAbove * checkCharacterBefore) +
            (checkRowAbove * checkCharacterAfter) +
            (checkRowBelow * numberOfDigitsForCurrentPart) +
            (checkRowBelow * checkCharacterBefore) +
            (checkRowBelow * checkCharacterAfter) +
            checkCharacterBefore + checkCharacterAfter;

    Index* indexesToCheck = malloc(totalNumberOfIndexesToCheck * sizeof(Index));
    int numberOfIndexesToCheck = 0;

    if (checkRowAbove) {
        const int rowAbove = row - 1;
        const int start = (column - numberOfDigitsForCurrentPart) - checkCharacterBefore;
        const int end = column + checkCharacterAfter;
        for (int columnToCheck = start; columnToCheck < end; columnToCheck++) {
            const Index index = { rowAbove, columnToCheck };
            indexesToCheck[numberOfIndexesToCheck++] = index;
        }
    }

    if (checkCharacterBefore) {
        const Index index = { row, column - numberOfDigitsForCurrentPart - 1 };
        indexesToCheck[numberOfIndexesToCheck++] = index;
    }

    if (checkCharacterAfter) {
        const Index index = { row, column };
        indexesToCheck[numberOfIndexesToCheck++] = index;
    }

    if (checkRowBelow) {
        const int rowBelow = row + 1;
        const int start = (column - numberOfDigitsForCurrentPart) - checkCharacterBefore;
        const int end = column + checkCharacterAfter;
        for (int columnToCheck = start; columnToCheck < end; columnToCheck++) {
            const Index index = {rowBelow, columnToCheck };
            indexesToCheck[numberOfIndexesToCheck++] = index;
        }
    }

    NeighbouringIndexes result = { indexesToCheck, numberOfIndexesToCheck };
    return result;
}

bool verifyNumberValidity(FILE* filePointer, Index* indexes, int numberOfIndexes, long columnWidth) {

    bool valid = false;
    long positionToReturnTo = ftell(filePointer);

    int i = 0;

    while (!valid && i < numberOfIndexes) {
        const Index index = indexes[i];

        long seekTo = (index.row * columnWidth) + index.column;
        fseek(filePointer, seekTo, SEEK_SET);
        int characterToCheck = getc(filePointer);
        valid = !isdigit(characterToCheck) && characterToCheck != '.' && characterToCheck != '\n';
        i++;
    }

    // Reset pointer so we can continue looping.
    fseek(filePointer, positionToReturnTo, SEEK_SET);
    return valid;
}

Index verifyNeighbouringGears(FILE* filePointer, Index* indexes, int numberOfIndexes, long columnWidth) {

    Index result = {-1, -1};
    long positionToReturnTo = ftell(filePointer);

    int i = 0;

    while (result.row < 0 && i < numberOfIndexes) {
        const Index index = indexes[i];

        long seekTo = (index.row * columnWidth) + index.column;
        fseek(filePointer, seekTo, SEEK_SET);
        int characterToCheck = getc(filePointer);
        if (characterToCheck == '*') {
            result = index;
        }
        i++;
    }

    // Reset pointer so we can continue looping.
    fseek(filePointer, positionToReturnTo, SEEK_SET);
    return result;
}

unsigned long solve03Part1() {

    unsigned long sumOfAllPartNumbers = 0;
    unsigned long numberOfColumns = 0;
    unsigned long numberOfRows = 0;

    int row = 0;
    readEveryLineForInput(3) {

        if (numberOfColumns == 0) {
            numberOfColumns = strlen(currentLine);
            numberOfRows = countNumberOfLines(filePointer, numberOfColumns);
        }

        for (int column = 0; column < numberOfColumns; column++) {
            int numberOfDigitsForCurrentPart = 0;

            while (isdigit(currentLine[column]) && column < numberOfColumns) {
                numberOfDigitsForCurrentPart++;
                column++;
            }


            if (numberOfDigitsForCurrentPart == 0) {
                continue;
            }

            NeighbouringIndexes neighbouringIndexes = findNeighbouringIndexes(
                row, column, numberOfRows, numberOfColumns, numberOfDigitsForCurrentPart
            );

            unsigned long numberToCheck =
                    parseLong(substring(currentLine, column - numberOfDigitsForCurrentPart, column));

            bool numberIsValid = verifyNumberValidity(
                filePointer,
                neighbouringIndexes.indexes,
                neighbouringIndexes.foundIndexes,
                numberOfColumns // NOLINT(*-narrowing-conversions)
            );

            if (numberIsValid) {
                sumOfAllPartNumbers += numberToCheck;
            }
        }

        row++;
    }

    return sumOfAllPartNumbers;
}

typedef struct PartAdjacentToGear {
    unsigned long partNumber;
    Index gearIndex;
} PartAdjacentToGear;


unsigned long solve03Part2() {

    unsigned long numberOfColumns = 0;
    unsigned long numberOfRows = 0;
    PartAdjacentToGear* partsAdjacentToGears = malloc(1000 * sizeof(PartAdjacentToGear));

    int row = 0;
    int partsFound = 0;
    readEveryLineForInput(3) {

        if (numberOfColumns == 0) {
            numberOfColumns = strlen(currentLine);
            numberOfRows = countNumberOfLines(filePointer, numberOfColumns);
        }

        for (int column = 0; column < numberOfColumns; column++) {
            int numberOfDigitsForCurrentPart = 0;

            while (isdigit(currentLine[column]) && column < numberOfColumns) {
                numberOfDigitsForCurrentPart++;
                column++;
            }

            if (numberOfDigitsForCurrentPart == 0) {
                continue;
            }

            NeighbouringIndexes neighbouringIndexes = findNeighbouringIndexes(
                row, column, numberOfRows, numberOfColumns, numberOfDigitsForCurrentPart
            );

            unsigned long numberToCheck =
                    parseLong(substring(currentLine, column - numberOfDigitsForCurrentPart, column));

            Index gearIndex = verifyNeighbouringGears(
                filePointer,
                neighbouringIndexes.indexes,
                neighbouringIndexes.foundIndexes,
                numberOfColumns // NOLINT(*-narrowing-conversions)
            );

            if (gearIndex.row != -1) {
                PartAdjacentToGear part = { numberToCheck, gearIndex };
                partsAdjacentToGears[partsFound++] = part;
            }
        }

        row++;
    }

    unsigned long sumOfAllGearRatios = 0;

    for (int i = 0; i < partsFound; i++) {
        PartAdjacentToGear part = partsAdjacentToGears[i];

        // We set the part number to zero for the indexes already added.
        if (part.partNumber == 0) {
            continue;
        }

        int indexOfSecondAdjacentPart = -1;
        for (int j = 0; j < partsFound; j++) {

            if (j == i) {
                continue;
            }

            PartAdjacentToGear potentialSecondPart = partsAdjacentToGears[j];
            if (part.gearIndex.row == potentialSecondPart.gearIndex.row &&
                part.gearIndex.column == potentialSecondPart.gearIndex.column) {

                if (indexOfSecondAdjacentPart == -1) {
                    indexOfSecondAdjacentPart = j;
                } else {
                    // We could be more efficient, but I need to cook lunch.
                    indexOfSecondAdjacentPart = -1;
                    j = partsFound;
                }
            }
        }

        if (indexOfSecondAdjacentPart != -1) {
            PartAdjacentToGear secondPart = partsAdjacentToGears[indexOfSecondAdjacentPart];
            sumOfAllGearRatios += part.partNumber * secondPart.partNumber;
            partsAdjacentToGears[i].partNumber = 0;
            partsAdjacentToGears[indexOfSecondAdjacentPart].partNumber = 0;
        }
    }

    return sumOfAllGearRatios;
}