#ifndef UtilitiesHeader
#define UtilitiesHeader

#include <stdio.h>
#include <stdlib.h>


// Types
typedef struct Position {
    int x;
    int y;
} Position;

// Math
#define parseLong(numberString) strtol(numberString, NULL, 10)
#define max(x, y) (x > y ? x : y)
#define min(x, y) (x < y ? x : y)
int countNumberOfDigitsInNumber(int number);
long gcd(long a, long b);
long lcm(long a, long b);
long lcmForArray(long *array, int arrayLength);

// String
char *replaceFirstOccurrence(char *currentString, const char *old, const char *new);
unsigned long indexOf(char *s, const char *substring, unsigned long startIndex);
char *insertStringInIndex(char *currentString, const char *stringToInsert, unsigned long index);
char *substring(const char *str, unsigned long start, unsigned long end);
long readNextSpaceSeparatedNumber(char *string, int *startingIndex);

// File
char readFileAtPosition(FILE* filePointer, Position position, int columnWidth);
FILE *readInput(int number);
int countNumberOfLines(FILE *filePointer, int numberOfColumns);
#define readEveryLineForInput(number) \
FILE *filePointer = readInput(number); \
char *currentLine = NULL; \
size_t currentLineLength = 0; \
while ((getline(&currentLine, &currentLineLength, filePointer)) != -1) \

#endif
