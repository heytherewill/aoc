#include <unistd.h>
#include <sys/syslimits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* readInput(int number) {
    char workingDirectory[PATH_MAX];
    if (getcwd(workingDirectory, sizeof(workingDirectory)) != NULL) {
        char inputNumber[3];
        sprintf(inputNumber, "%02d", number);
        char* relativePath = "/../inputs/";
        char* fileExtension = ".txt";
        char* path = malloc(
            strlen(workingDirectory) +
            strlen(relativePath) +
            strlen(inputNumber) +
            strlen(fileExtension) + 1
        );

        strcpy(path, workingDirectory);
        strcat(path, relativePath);
        strcat(path, inputNumber);
        strcat(path, fileExtension);

        FILE* filePointer = fopen(path,"r");
        return filePointer;
    }

    return NULL;
}