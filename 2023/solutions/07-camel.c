#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "../utilities/file.h"
#include "../utilities/math.h"
#include "../utilities/string.h"

#define handSize 5

typedef enum HandType {
    FiveOfAKind,
    FourOfAKind,
    FullHouse,
    ThreeOfAKind,
    TwoPair,
    OnePair,
    HighCard
} HandType;

typedef struct Hand {
    char cards[handSize];
    long bid;
    HandType handType;
} Hand;

static bool countJokers = false;

static int powerForCard(const char card) {
    switch (card) {
        case 'A':
            return 14;
        case 'K':
            return 13;
        case 'Q':
            return 12;
        case 'J':
            return countJokers ? 1 : 11;
        case 'T':
            return 10;
        default: {
            char string[2];
            string[0] = card;
            string[1] = '\0';
            return parseLong(string);
        }
    }
}

static int compareInts(const void* a, const void* b) {
    const int intA = *((int*) a);
    const int intB = *((int*) b);
    return intA == intB ? 0 : intA > intB ? -1 : 1;
}

static int compareCards(const char cardA, const char cardB) {
    const int powerOfCardA = powerForCard(cardA);
    const int powerOfCardB = powerForCard(cardB);
    return powerOfCardA == powerOfCardB ? 0 : powerOfCardA > powerOfCardB ? 1 : -1;
}

static int compareHands(const void* a, const void* b) {
    const Hand handA = *((Hand*) a);
    const Hand handB = *((Hand*) b);

    if (handA.handType == handB.handType) {
        int i = 0;
        do {
            int diff = compareCards(handA.cards[i], handB.cards[i]);
            if (diff != 0) {
                return diff;
            }

            i++;
        } while (i < handSize);

        return 0;
    } else if (handA.handType > handB.handType) {
        return -1;
    } else {
        return 1;
    }
}

static int* countNumberOfDifferentCardsInHand(const char cards[handSize]) {
    char buckets[handSize];
    int* result = malloc(handSize * sizeof(int));

    int jokerCount = 0;
    int numberOfDifferentCards = 0;

    for (int i = 0; i < handSize; i++) {
        result[i] = 0;
        char card = cards[i];
        if (countJokers && card == 'J') {
            jokerCount++;
            continue;
        }

        bool alreadyInBuckets = false;
        int j = 0;
        do {
            alreadyInBuckets = buckets[j] == card;
        } while (!alreadyInBuckets && j++ < numberOfDifferentCards);

        if (alreadyInBuckets) {
            result[j] = result[j] + 1;
            continue;
        }

        buckets[numberOfDifferentCards] = card;
        result[numberOfDifferentCards++] = 1;
    }

    qsort( result, handSize, sizeof(int), compareInts);
    result[0] = result[0] + jokerCount;
    return result;
}

static Hand parseHand(char *line) {
    Hand result;
    int i;
    for (i = 0; i < handSize; i++) {
        result.cards[i] = line[i];
    }

    while(line[i] == ' ') { i++; }
    result.bid = readNextSpaceSeparatedNumber(line, &i);

    int* counts = countNumberOfDifferentCardsInHand(result.cards);

    if (counts[0] == 5) {
        result.handType = FiveOfAKind;
    } else if (counts[0] == 4) {
        result.handType = FourOfAKind;
    } else if (counts[0] == 3) {
        if (counts[1] == 2) {
            result.handType = FullHouse;
        } else {
            result.handType = ThreeOfAKind;
        }
    } else if (counts[0] == 2) {
        if (counts[1] == 2) {
            result.handType = TwoPair;
        } else {
            result.handType = OnePair;
        }
    } else {
        result.handType = HighCard;
    }

    return result;
}

static long solve() {
    int currentHand = 0;
    int numberOfHands = 1000;
    Hand *hands = malloc(numberOfHands * sizeof(Hand));

    readEveryLineForInput(7) {
        hands[currentHand++] = parseHand(currentLine);
    }
    fclose(filePointer);

    qsort( hands, numberOfHands, sizeof(Hand), compareHands);

    long sumOfAllBids = 0;
    for (int i = 0; i < currentHand; ++i) {
        const Hand hand = hands[i];
        sumOfAllBids += hand.bid * (i + 1);
    }

    return sumOfAllBids;
}

long solve07Part1() {
    countJokers = false;
    return solve();
}

long solve07Part2() {
    countJokers = true;
    return solve();
}