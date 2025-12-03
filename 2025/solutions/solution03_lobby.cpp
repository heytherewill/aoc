#include "../utilities/file.h"
#include <sstream>

static long joltageForLine(std::string &line, int expectedLength) {

    const unsigned long numberOfBatteries = line.size();
    std::string finalJoltage;
    auto currentIndex = -1;
    do {
        auto bestDigitSoFar = 0;
        for (int i = currentIndex + 1; i < numberOfBatteries - expectedLength + 1 + finalJoltage.length(); i++) {
            auto digit = std::stoi(line.substr(i, 1));
            if (digit > bestDigitSoFar) {
                bestDigitSoFar = digit;
                currentIndex = i;
            }
        }

        finalJoltage += std::to_string(bestDigitSoFar);

    } while (finalJoltage.length() < expectedLength);

    return std::stol(finalJoltage);
}

long solveDay03Part01() {
    auto sum = 0L;
    auto file = readInput(3);
    std::string line;
    while (std::getline(file, line)) {
        sum += joltageForLine(line, 2);;
    }

    return sum;
}

long solveDay03Part02() {
    auto sum = 0L;
    auto file = readInput(3);
    std::string line;
    while (std::getline(file, line)) {

        sum += joltageForLine(line, 12);
    }

    return sum;
}