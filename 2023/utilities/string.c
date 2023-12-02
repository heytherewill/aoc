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
    s += startIndex;

    char *result = strstr(s, substring);

    if (result != NULL) {
        return (result - s) + startIndex;
    } else {
        return -1;
    }
}

char* insertStringInIndex(char* currentString, const char* stringToInsert, unsigned long index) {
    size_t resultLength = strlen(currentString) + strlen(stringToInsert);

    char* result = (char*)malloc((resultLength + 1) * sizeof(char));

    strncpy(result, currentString, index);
    result[index] = '\0';
    strcat(result, stringToInsert);
    strcat(result, currentString + index);

    return result;
}

char* substring(const char* str, unsigned long start, unsigned long end) {
    unsigned long length = end - start;

    char* result = (char*)malloc((length + 1) * sizeof(char));
    strncpy(result, str + start, length);
    result[length] = '\0';

    return result;
}
