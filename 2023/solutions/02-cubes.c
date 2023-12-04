#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../utilities/file.h"
#include "../utilities/string.h"
#include "../utilities/math.h"

typedef struct GameInfo {
    unsigned long inputStartIndex;
    unsigned long gameId;
} GameInfo;

typedef struct BallCount {
    int red;
    int green;
    int blue;
} BallCount;

static GameInfo parseGameId(char* currentLine) {
    unsigned long indexOfSpace = indexOf(currentLine, " ", 0);
    unsigned long indexOfColon = indexOf(currentLine, ":", 0);
    char* gameId = substring(currentLine, indexOfSpace + 1, indexOfColon);
    GameInfo gameInfo = { indexOfColon + 2, parseLong(gameId) };
    return gameInfo;
}

static BallCount countBallsForLine(
    char *currentLine,
    const unsigned long startingIndex
) {
    const unsigned long currentLineLength = strlen(currentLine);
    BallCount result = { 0, 0, 0 };
    unsigned long i = startingIndex;
    do {
        unsigned long startingIndexOfBallAmount = i;
        do { i++; } while (isdigit(currentLine[i]));
        unsigned long endIndexOfBallAmount = i;
        unsigned long amountOfBalls = parseLong(
            substring(currentLine, startingIndexOfBallAmount, endIndexOfBallAmount)
        );

        // One extra increment to get rid of the space
        switch (currentLine[++i]) {
            case 'r':
                result.red = max(result.red, amountOfBalls);
                i+= 3;
                break;
            case 'g':
                result.green = max(result.green, amountOfBalls);
                i+= 5;
                break;
            case 'b':
                result.blue = max(result.blue, amountOfBalls);
                i+= 4;
                break;
        }

        // Space and semi-colon
        i+= 2;
    } while (i < currentLineLength);


    return result;
}


unsigned long solve02Part1() {

    const BallCount maxValidBallCount = { 12, 13, 14 };
    unsigned long sumOfPossibleGameIds = 0;

    readEveryLineForInput(2) {
        GameInfo gameInfo = parseGameId(currentLine);

        BallCount visibleBallCount =
            countBallsForLine(currentLine,gameInfo.inputStartIndex);

        bool gameIsPossible =
            visibleBallCount.red <= maxValidBallCount.red &&
            visibleBallCount.green <= maxValidBallCount.green &&
            visibleBallCount.blue <= maxValidBallCount.blue;

        if (gameIsPossible) {
            sumOfPossibleGameIds += gameInfo.gameId;
        }
    }

    fclose(filePointer);

    return sumOfPossibleGameIds;
}

unsigned long solve02Part2() {

    unsigned long sumOfPowerOfSets = 0;

    readEveryLineForInput(2) {
        GameInfo gameInfo = parseGameId(currentLine);

        BallCount visibleBallCount =
            countBallsForLine(currentLine,gameInfo.inputStartIndex);

        unsigned long setPower =
            visibleBallCount.red * visibleBallCount.green * visibleBallCount.blue;

        sumOfPowerOfSets += setPower;
    }

    fclose(filePointer);

    return sumOfPowerOfSets;
}