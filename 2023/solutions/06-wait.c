#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "../utilities/utilities.h"

static int parseAsListOfLongs(char *string, long *listOfLongs) {
    int numberOfIntegersFound = 0;
    unsigned long lineLength = strlen(string);
    int i = 0;
    while(i < lineLength && string[i] != '\0' && string[i] != '\n') {
        if (!isdigit(string[i])) {
            i++;
            continue;
        }

        long parsedNumber = readNextSpaceSeparatedNumber(string, &i);
        listOfLongs[numberOfIntegersFound++] = parsedNumber;
    }

    return numberOfIntegersFound;
}

static long parseAsASingleLong(char *string) {
    unsigned long lineLength = strlen(string);
    int i = 0;
    char *digits = malloc(50);
    int numberOfDigits = 0;
    while(i < lineLength && string[i] != '\0' && string[i] != '\n') {
        if (!isdigit(string[i])) {
            i++;
            continue;
        } else {
            digits[numberOfDigits++] = string[i++];
        }
    }

    digits[numberOfDigits] = '\0';
    long parsedNumber = parseLong(digits);
    return parsedNumber;
}

static long calculateNumberOfWaysOfWinning(long maxAllowedTime, long recordToBeat) {
    long minTime = 999999999;
    long timePressing = 1;
    while (minTime == 999999999 && timePressing <= maxAllowedTime) {

        long timeMoving = maxAllowedTime - timePressing;
        long traveledDistance = timeMoving * timePressing;
        if (traveledDistance > recordToBeat) {
            minTime = timePressing;
        } else {
            timePressing++;
        }
    }

    timePressing = maxAllowedTime;
    long maxTime = 0;
    while (maxTime == 0 && timePressing > minTime) {

        long timeMoving = maxAllowedTime - timePressing;
        long traveledDistance = timeMoving * timePressing;
        if (traveledDistance > recordToBeat) {
            maxTime = timePressing;
        } else {
            timePressing--;
        }
    }

    long numberOfWaysOfWinning = (max(maxTime, minTime)) - minTime + 1;
    return numberOfWaysOfWinning;
}

long solve06Part1() {

    int numberOfRaces = 0;
    long *allowedTimes = malloc(10000 * sizeof(long));
    long *records = malloc( 10000 * sizeof(long));
    bool recordWereParsed = false;

    readEveryLineForInput(6) {
        if (numberOfRaces == 0) {
            numberOfRaces = parseAsListOfLongs(currentLine, allowedTimes);
        } else if (!recordWereParsed) {
            parseAsListOfLongs(currentLine, records);
            recordWereParsed = true;
        }
    }
    fclose(filePointer);

    long productOfWaysOfWinning = 1;
    for (int i = 0; i < numberOfRaces; ++i) {
        long recordToBeat = records[i];
        long maxAllowedTime = allowedTimes[i];
        long numberOfWaysOfWinning = calculateNumberOfWaysOfWinning(maxAllowedTime, recordToBeat);
        productOfWaysOfWinning *= numberOfWaysOfWinning;
    }

    return productOfWaysOfWinning;
}


long solve06Part2() {

    long maxAllowedTime = 0;
    long recordToBeat = 0;

    readEveryLineForInput(6) {
        if (maxAllowedTime == 0) {
            maxAllowedTime = parseAsASingleLong(currentLine);
        } else if (recordToBeat == 0) {
            recordToBeat = parseAsASingleLong(currentLine);
        }
    }
    fclose(filePointer);

    long numberOfWaysOfWinning = calculateNumberOfWaysOfWinning(maxAllowedTime, recordToBeat);
    return numberOfWaysOfWinning;
}