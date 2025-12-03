#pragma once

#include <unistd.h>
#include <sys/syslimits.h>
#include <fstream>
#include <format>
#include <string>

std::ifstream readInput(const int number) {
    char workingDirectory[PATH_MAX];
    getcwd(workingDirectory, sizeof(workingDirectory));
    const std::string inputNumber = std::format("{:02}", number);
    const std::string relativePath = "/../inputs/";
    const std::string fileExtension = ".txt";
    const std::string path = workingDirectory + relativePath + inputNumber + fileExtension;
    std::ifstream fileStream(path);
    return fileStream;
}
