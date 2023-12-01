#include <string.h>
#include <stdlib.h>

char* replaceFirstOccurrence(char* currentString, const char* old, const char* new) {
    char* p = strstr(currentString, old);
    size_t lengthOfOldString = strlen(old);
    size_t lengthOfNewString = strlen(new);

    if (p != NULL) {
        if (lengthOfOldString != lengthOfNewString) {
            memmove(p + lengthOfNewString, p + lengthOfOldString, strlen(p + lengthOfOldString) + 1);
        }

        memcpy(p, new, lengthOfNewString);
    }

    return currentString;
}

unsigned long indexOf(char* s, const char* substring, unsigned long startIndex) {
    unsigned long mainLen = strlen(s);
    if (startIndex >= mainLen) {
        return -1;
    }

    s += startIndex;

    char *result = strstr(s, substring);

    if (result != NULL) {
        return (result - s) + startIndex;
    } else {
        // Substring not found
        return -1;
    }
}

char* insertStringInIndex(char* currentString, const char* stringToInsert, unsigned long index) {
    // Calculate the length of the resulting string
    size_t resultLength = strlen(currentString) + strlen(stringToInsert);

    // Allocate memory for the new string
    char* result = (char*)malloc((resultLength + 1) * sizeof(char));

    if (result == NULL) {
        // Memory allocation failed
        return NULL;
    }

    strncpy(result, currentString, index);
    result[index] = '\0';
    strcat(result, stringToInsert);
    strcat(result, currentString + index);

    return result;
}