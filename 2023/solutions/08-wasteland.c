#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../utilities/file.h"
#include "../utilities/math.h"
#include "../utilities/string.h"
#include <search.h>

static long solve(bool simultaneousCheck) {
    int numberOfDirections = 0;

    int firstIndexThatMustMatch = simultaneousCheck ? 2 : 0;

    int numberOfStartingPoints = 0;
    char **entryKey = malloc(1000 * sizeof(char));
    char *directions;
    hcreate(2000);

    ENTRY hashTableEntry;
    ENTRY *hashTableEntryPointer;

    readEveryLineForInput(8) {
        if (numberOfDirections == 0) {
            unsigned long lineLength = strlen(currentLine) - 1;
            directions = malloc(lineLength * sizeof(char));
            for (numberOfDirections = 0; numberOfDirections < lineLength; numberOfDirections++) {
                directions[numberOfDirections] = currentLine[numberOfDirections];
            }
        } else if (currentLine[0] != '\n') {
            char *mapEntry = malloc(6 * sizeof(char));
            mapEntry[0] = currentLine[7];
            mapEntry[1] = currentLine[8];
            mapEntry[2] = currentLine[9];
            mapEntry[3] = currentLine[12];
            mapEntry[4] = currentLine[13];
            mapEntry[5] = currentLine[14];

            hashTableEntry.key = malloc(3 * sizeof(char));
            hashTableEntry.key[0] = currentLine[0];
            hashTableEntry.key[1] = currentLine[1];
            hashTableEntry.key[2] = currentLine[2];
            hashTableEntry.data = (void *)mapEntry;
            hashTableEntryPointer = hsearch(hashTableEntry, ENTER);
            /* there should be no failures */
            if (hashTableEntryPointer == NULL) {
                fprintf(stderr, "entry failed\n");
                exit(EXIT_FAILURE);
            }

            bool startingPoint = true;
            for (int i = firstIndexThatMustMatch; i < 3; ++i) {
                startingPoint &= hashTableEntry.key[i] == 'A';
            }

            if (startingPoint) {
                entryKey[numberOfStartingPoints] = malloc(3 * sizeof(char));
                entryKey[numberOfStartingPoints][0] = hashTableEntry.key[0];
                entryKey[numberOfStartingPoints][1] = hashTableEntry.key[1];
                entryKey[numberOfStartingPoints++][2] = hashTableEntry.key[2];
            }
        }
    }
    fclose(filePointer);


    long *stepsPerStart = malloc(numberOfStartingPoints * sizeof(long));

    for (int startingPoint = 0; startingPoint < numberOfStartingPoints; startingPoint++) {

        char currentKey[3];
        memcpy(currentKey, entryKey[startingPoint], 3);
        bool found = false;
        long steps = 0;
        int currentDirection = 0;
        do {
            steps++;
            hashTableEntry.key = currentKey;
            hashTableEntryPointer = hsearch(hashTableEntry, FIND);
            const char* foundEntry = ((char *)(hashTableEntryPointer->data));

            char direction = directions[currentDirection];
            int startingIndex = direction == 'L' ? 0 : 3;

            for (int i = 0; i < 3; ++i) {
                currentKey[i] = foundEntry[startingIndex + i];
            }

            bool match = true;
            for (int i = firstIndexThatMustMatch; i < 3; ++i) {
                match &= currentKey[i] == 'Z';
            }

            found = match;
            currentDirection = (currentDirection + 1) % numberOfDirections;

            stepsPerStart[startingPoint] = steps;

        } while (!found);
    }

    if (numberOfStartingPoints == 1) {
        return stepsPerStart[0];
    } else {
        return lcmForArray(stepsPerStart, numberOfStartingPoints);
    }
}

long solve08Part1() {
    return solve(false);
}

long solve08Part2() {
    return solve(true);
}