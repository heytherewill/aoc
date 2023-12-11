#include <string.h>
#include <search.h>
#include "../utilities/utilities.h"

static long solve(int emptyLineDistance) {

    int numberOfColumns = 0;
    int galaxiesFound = 0;
    Position *galaxies = malloc(9999 * sizeof(int));
    int **skyMap = malloc(1000 * sizeof(int));
    int *galaxiesFoundInColumn;
    int numberOfRows = 0;

    readEveryLineForInput(11) {

        if (numberOfColumns == 0) {
            numberOfColumns = strlen(currentLine); // NOLINT(*-narrowing-conversions)
            galaxiesFoundInColumn = malloc(numberOfColumns * sizeof(int));
            for (int i = 0; i < numberOfColumns; ++i) {
                galaxiesFoundInColumn[i] = 0;
            }
        }

        int previousNumberOfFoundGalaxies = galaxiesFound;

        skyMap[numberOfRows] = malloc(numberOfColumns * sizeof(int));
        for (int x = 0; x < numberOfColumns; x++) {
            skyMap[numberOfRows][x] = 1;

            if (currentLine[x] == '#') {
                const Position position = {x, numberOfRows };
                galaxies[galaxiesFound++] = position;
                galaxiesFoundInColumn[x] = galaxiesFoundInColumn[x] + 1;
            }
        }

        // If no galaxies were found then we should double the size of this entire row.
        if (previousNumberOfFoundGalaxies == galaxiesFound) {
            for (int x = 0; x < numberOfColumns; x++) {
                skyMap[numberOfRows][x] = emptyLineDistance;
            }
        }

        numberOfRows++;
    }

    for (int x = 0; x < numberOfColumns; ++x) {
        // If no galaxies were found then we should double the size of this entire column.
        if (galaxiesFoundInColumn[x] == 0) {
            for (int y = 0; y < numberOfRows; ++y) {
                skyMap[y][x] = emptyLineDistance;
            }
        }
    }

    long sumOfShortestPaths = 0;
    for (int i = 0; i < galaxiesFound; ++i) {
        const Position homeGalaxy = galaxies[i];
        for (int j = 0; j < galaxiesFound; ++j) {
            if (i == j) {
                continue;
            }

            const Position targetGalaxy = galaxies[j];

            const int xDirection = homeGalaxy.x > targetGalaxy.x ? -1 : 1;
            const int yDirection = homeGalaxy.y > targetGalaxy.y ? -1 : 1;

            long manhattanDistance = 0;

            for (int x = homeGalaxy.x; x < targetGalaxy.x; x += xDirection) {
                manhattanDistance+= skyMap[homeGalaxy.y][x];
            }

            for (int y = homeGalaxy.y; y < targetGalaxy.y; y += yDirection) {
                manhattanDistance+= skyMap[y][targetGalaxy.x];
            }

            sumOfShortestPaths += manhattanDistance;
        }
    }

    return sumOfShortestPaths;
}

long solve11Part1() {
    return solve(2);
}

long solve11Part2() {
    return solve(1000000);
}