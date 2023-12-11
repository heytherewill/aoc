#include <string.h>
#include <stdbool.h>
#include <search.h>
#include "../utilities/utilities.h"

typedef enum Direction {
    North,
    South,
    East,
    West
} Direction;

void travelInPipe(char pipe, Position *currentPosition, Direction *travelingDirection) {
    const Direction currentTravelingDirection = *travelingDirection;
    switch (pipe) {
        case 'F':
            currentPosition->x += currentTravelingDirection == North ? 1 : 0;
            currentPosition->y += currentTravelingDirection == West ? 1 : 0;
            (*travelingDirection) = currentTravelingDirection == West ? South : East;
            break;
        case 'L':
            currentPosition->x += currentTravelingDirection == South ? 1 : 0;
            currentPosition->y += currentTravelingDirection == West ? -1 : 0;
            (*travelingDirection) = currentTravelingDirection == West ? North : East;
            break;
        case 'J':
            currentPosition->x += currentTravelingDirection == South ? -1 : 0;
            currentPosition->y += currentTravelingDirection == East ? -1 : 0;
            (*travelingDirection) = currentTravelingDirection == East ? North : West;
            break;
        case '7':
            currentPosition->x += currentTravelingDirection == North ? -1 : 0;
            currentPosition->y += currentTravelingDirection == East ? 1 : 0;
            (*travelingDirection) = currentTravelingDirection == East ? South : West;
            break;
        case '-':
            currentPosition->x += currentTravelingDirection == West ? -1 : currentTravelingDirection == East ? 1 : 0;
            (*travelingDirection) = currentTravelingDirection == West ? West : East;
            break;
        case '|':
            currentPosition->y += currentTravelingDirection == North ? -1 : currentTravelingDirection == South ? 1 : 0;
            (*travelingDirection) = currentTravelingDirection == North ? North : South;
            break;
        default:
            break;
    }
}

char *keyForPosition(Position position) {
    int digitsInX = countNumberOfDigitsInNumber(position.x);
    char *xString = malloc(digitsInX * sizeof(char) + 2);
    sprintf(xString, "x%d", position.x);

    int digitsInY = countNumberOfDigitsInNumber(position.y);
    char *yString = malloc(digitsInY * sizeof(char) + 2);
    sprintf(yString, "y%d", position.y);

    return insertStringInIndex(xString, yString, digitsInX + 1);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"
long addAllTilesInMazeToMap( FILE* filePointer, const Position startingPosition, int numberOfColumns) {

    hcreate(99999);
    Position currentPosition;
    Direction travelingDirection;
    ENTRY hashTableEntry;

    hashTableEntry.key = keyForPosition(startingPosition);
    hashTableEntry.data = (void *)'S';
    hsearch(hashTableEntry, ENTER);

    for (int i = 0; i < 4; ++i) {

        int distanceOneX = startingPosition.x + (i == 2 ? 1 : i == 3 ? -1 : 0);
        int distanceOneY = startingPosition.y + (i == 1 ? 1 : i == 0 ? -1 : 0);

        if (distanceOneX < 0 || distanceOneY < 0) {
            continue;
        }

        Position position = {distanceOneX, distanceOneY};
        Direction direction = i;

        char nextPipe = readFileAtPosition(filePointer, position, numberOfColumns);
        travelInPipe(nextPipe, &position, &direction);

        if (position.x != distanceOneX || position.y != distanceOneY) {
            travelingDirection = i;
            currentPosition.x = distanceOneX;
            currentPosition.y = distanceOneY;
        }
    }

    long stepCount = 1;
    do {
        char currentPipe = readFileAtPosition(filePointer, currentPosition, numberOfColumns);
        hashTableEntry.key = keyForPosition(currentPosition);
        hashTableEntry.data = (void *)(currentPipe);
        hsearch(hashTableEntry, ENTER);

        travelInPipe(currentPipe, &currentPosition, &travelingDirection);
        stepCount++;
    } while (currentPosition.x != startingPosition.x || currentPosition.y != startingPosition.y);

    return stepCount;
}
#pragma clang diagnostic pop

long solve10Part1() {

    int numberOfColumns = 0;
    Position startingPosition;
    int currentRow = 0;

    readEveryLineForInput(10) {

        if (numberOfColumns == 0) {
            numberOfColumns = strlen(currentLine); // NOLINT(*-narrowing-conversions)
        }

        for (int i = 0; i < numberOfColumns; ++i) {
            if (currentLine[i] == 'S') {
                startingPosition.x = i;
                startingPosition.y = currentRow;
            }
        }

        currentRow++;
    }

    long stepCount = addAllTilesInMazeToMap(filePointer, startingPosition, numberOfColumns);
    long maxDistance = stepCount / 2;
    return maxDistance;
}

long solve10Part2() {

    int numberOfColumns = 0; // NOLINT(*-narrowing-conversions)
    int numberOfRows = 0;
    Position startingPosition;

    readEveryLineForInput(10) {
        if (numberOfColumns == 0) {
            numberOfColumns = strlen(currentLine); // NOLINT(*-narrowing-conversions)
        }

        for (int i = 0; i < numberOfColumns; ++i) {
            if (currentLine[i] == 'S') {
                startingPosition.x = i;
                startingPosition.y = numberOfRows;
            }
        }

        numberOfRows++;
    }

    addAllTilesInMazeToMap(filePointer, startingPosition, numberOfColumns);

    ENTRY hashTableEntry;
    int numberOfTilesContained = 0;
    Position position;
    for (int y = 0; y < numberOfRows; ++y) {
        bool currentlyInside = false;
        for (int x = 0; x < numberOfColumns; ++x) {
            position.x = x;
            position.y = y;
            char pipe = readFileAtPosition(filePointer, position, numberOfColumns);
            hashTableEntry.key = keyForPosition(position);
            bool tileIsPartOfTheLoop = hsearch(hashTableEntry, FIND) != NULL;
            if (tileIsPartOfTheLoop && (pipe == '|' || pipe == '7' || pipe == 'F')) {
                currentlyInside = !currentlyInside;
            }

            numberOfTilesContained += !tileIsPartOfTheLoop && currentlyInside;
        }
    }

    return numberOfTilesContained;
}