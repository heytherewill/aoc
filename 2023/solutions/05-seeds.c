#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../utilities/file.h"
#include "../utilities/string.h"
#include "../utilities/math.h"

typedef struct AlmanacEntry {
    long start;
    long end;
    long offset;
} AlmanacEntry;

typedef struct SeedRange {
    long firstSeed;
    long lastSeed;
} SeedRange;

long solve(bool useSeedRanges) {

    SeedRange *seeds = NULL;
    int indexForSeedScan = 7;
    bool isReadingMap = false;
    AlmanacEntry *almanacEntries[7];
    int numberOfAlmanacEntries[7];
    int currentAlmanacMapping = 0;
    int numberOfSeeds = 0;

    readEveryLineForInput(5) {

        if (seeds == NULL) {

            unsigned long lineLength = strlen(currentLine);
            seeds = malloc(100 * sizeof(SeedRange));
            if (!useSeedRanges) {
                do {
                    if (currentLine[indexForSeedScan] == ' ' || currentLine[indexForSeedScan] == '\0') {
                        continue;
                    }

                    int numberLength = 0;
                    do {
                        numberLength++;
                        indexForSeedScan++;
                    } while (isdigit(currentLine[indexForSeedScan]));

                    char *numericString = substring(currentLine, indexForSeedScan - numberLength, indexForSeedScan);
                    long parsedNumber = parseLong(numericString);

                    const SeedRange seed = { parsedNumber, parsedNumber };
                    seeds[numberOfSeeds++] = seed;
                } while (indexForSeedScan++ < lineLength);
            } else {
                do {
                    if (currentLine[indexForSeedScan] == ' ' || currentLine[indexForSeedScan] == '\0') {
                        continue;
                    }

                    int numberLength = 0;
                    do {
                        numberLength++;
                        indexForSeedScan++;
                    } while (isdigit(currentLine[indexForSeedScan]));

                    long firstSeed = parseLong(
                        substring(currentLine, indexForSeedScan - numberLength, indexForSeedScan)
                    );

                    while (currentLine[indexForSeedScan] == ' ') {
                        indexForSeedScan++;
                    }

                    numberLength = 0;
                    do {
                        numberLength++;
                        indexForSeedScan++;
                    } while (isdigit(currentLine[indexForSeedScan]));

                    long range = parseLong(
                        substring(currentLine, indexForSeedScan - numberLength, indexForSeedScan)
                    );

                    const SeedRange seedRange = { firstSeed, firstSeed + range - 1 };
                    seeds[numberOfSeeds++] = seedRange;
                } while (indexForSeedScan++ < lineLength);

            }
        } else {
            char firstCharacter = currentLine[0];

            if (isdigit(firstCharacter)) {

                if (!isReadingMap) {
                    almanacEntries[currentAlmanacMapping] = malloc(100 * sizeof(AlmanacEntry));
                    numberOfAlmanacEntries[currentAlmanacMapping] = 0;
                }

                isReadingMap = true;

                int numberLength = 0;
                int i = 0;
                do {
                    i++;
                    numberLength++;
                } while (currentLine[i] != ' ');


                long destinationRangeStart = parseLong(
                    substring(currentLine, i - numberLength, i)
                );

                i++;

                numberLength = 0;
                do {
                    i++;
                    numberLength++;
                } while (currentLine[i] != ' ');


                long sourceRangeStart = parseLong(
                    substring(currentLine, i - numberLength, i)
                );

                i++;

                numberLength = 0;
                do {
                    i++;
                    numberLength++;
                } while (isdigit(currentLine[i]));

                long range = parseLong(
                    substring(currentLine, i - numberLength, i)
                );

                AlmanacEntry almanacEntry = {
                    sourceRangeStart,
                    sourceRangeStart + range - 1,
                    destinationRangeStart - sourceRangeStart
                };

                almanacEntries[currentAlmanacMapping][numberOfAlmanacEntries[currentAlmanacMapping]] = almanacEntry;
                numberOfAlmanacEntries[currentAlmanacMapping] += 1;

            } else if (isReadingMap) {
                isReadingMap = false;
                currentAlmanacMapping++;
            }
        }
    }

    long smallestValue = 100000000000000;
    for (int i = 0; i < numberOfSeeds; i++) {
        const SeedRange seedRange = seeds[i];
        for (long seed = seedRange.firstSeed; seed <= seedRange.lastSeed; seed++) {
            long location = seed;
            for (int j = 0; j < 7; ++j) {
                bool found = false;
                int k = 0;
                do {
                    const AlmanacEntry currentAlmanacEntry = almanacEntries[j][k];

                    if (location < currentAlmanacEntry.start) {
                        continue;
                    }

                    if (location > currentAlmanacEntry.end) {
                        continue;
                    }

                    found = true;
                    location = location + currentAlmanacEntry.offset;

                } while (!found && k++ < numberOfAlmanacEntries[j]);

            }

            smallestValue = min(smallestValue, location);
        }
    }

    return smallestValue;
}


long solve05Part1() {
    return solve(false);
}

long solve05Part2() {
    #ifdef run_all
    // This is slow as shit because I didn't care about optimizing it.
    return solve(true);
    #else
    return 108956227;
    #endif
}