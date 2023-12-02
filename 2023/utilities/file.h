#include <stdio.h>

FILE* readInput(int number);

#define readEveryLineForInput(number) \
FILE* filePointer = readInput(number); \
char* currentLine = NULL; \
size_t currentLineLength = 0; \
while ((getline(&currentLine, &currentLineLength, filePointer)) != -1)