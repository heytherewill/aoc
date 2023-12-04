#include <ctype.h>
#include <math.h>
#include <string.h>
#include "../utilities/file.h"
#include "../utilities/math.h"
#include "../utilities/string.h"

static int playGame(char* currentLine, int currentGame) {
    int digitsInNumber = countNumberOfDigitsInNumber(currentGame);
    int currentIndex = 7 + digitsInNumber;

    int foundWinningNumbers = 0;
    int *winningNumbers = malloc(5 * sizeof(int));

    unsigned long separationMarker = indexOf(currentLine, "|", 0);
    unsigned long lineLength = strlen(currentLine);

    do {
        while (currentLine[currentIndex] == ' ') {
            currentIndex++;
        }

        int numberLength = 0;
        do {
            numberLength++;
            currentIndex++;
        } while (isdigit(currentLine[currentIndex]));

        int parsedNumber = parseLong(
            substring(currentLine, currentIndex - numberLength, currentIndex)
        );

        if (parsedNumber > 0) {
            winningNumbers[foundWinningNumbers++] = parsedNumber;
        }
    } while (currentIndex < separationMarker);

    currentIndex = separationMarker + 2; // NOLINT(*-narrowing-conversions)

    int numberOfWinningNumbersInTicket = 0;
    do {
        while (currentLine[currentIndex] == ' ') {
            currentIndex++;
        }

        int numberLength = 0;
        do {
            numberLength++;
            currentIndex++;
        } while (isdigit(currentLine[currentIndex]));

        int parsedNumber = parseLong(
                substring(currentLine, currentIndex - numberLength, currentIndex)
        );

        int currentWinningNumberIndex = 0;
        do {
            int currentWinningNumber = winningNumbers[currentWinningNumberIndex++];
            numberOfWinningNumbersInTicket += currentWinningNumber == parsedNumber;
        } while (currentWinningNumberIndex < foundWinningNumbers);
    } while (currentIndex < lineLength);

    return numberOfWinningNumbersInTicket;
}

long solve04Part1() {
    int currentGame = 1;
    int sumOfAllWinningGames = 0;
    readEveryLineForInput(4) {
        int numberOfWinningNumbersInTicket = playGame(currentLine, currentGame++);
        sumOfAllWinningGames += pow(2, numberOfWinningNumbersInTicket) / 2; // NOLINT(*-narrowing-conversions)
    }

    return sumOfAllWinningGames;
}

long solve04Part2() {

    int gamesPlayed = 1;
    int currentGame = 1;
    int currentGameIndex = 0;
    int numberOfGames = 0;
    int* amountOfScratchCards;
    int* memoizedGameResults;

    readEveryLineForInput(4) {

        if (numberOfGames == 0) {
            int columnCount = strlen(currentLine); // NOLINT(*-narrowing-conversions)
            numberOfGames = countNumberOfLines(filePointer, columnCount);
            amountOfScratchCards = malloc(numberOfGames * sizeof(int));
            memoizedGameResults = malloc(numberOfGames * sizeof(int));

            for (int i = 0; i < numberOfGames; i++) {
                amountOfScratchCards[i] = 1;
                memoizedGameResults[i] = -1;
            }
        }

        while (amountOfScratchCards[currentGameIndex] != 0) {
            amountOfScratchCards[currentGameIndex] = amountOfScratchCards[currentGameIndex] - 1;

            int numberOfWinningNumbersInTicket =
                memoizedGameResults[currentGameIndex] == -1
                ? playGame(currentLine, currentGame)
                : memoizedGameResults[currentGameIndex];

            memoizedGameResults[currentGameIndex] = numberOfWinningNumbersInTicket;

            for (int i = currentGame; i < currentGame + numberOfWinningNumbersInTicket; i++) {
                amountOfScratchCards[i] = amountOfScratchCards[i] + 1;
            }

            gamesPlayed++;
        }

        currentGame++;
        currentGameIndex++;
    }

    return gamesPlayed;
}