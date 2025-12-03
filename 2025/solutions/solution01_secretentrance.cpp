#include <string>
#include "../utilities/file.h"

long solveDay01Part01() {
    auto zeroCount = 0L;
    auto currentPosition = 50;
    auto file = readInput(1);
    std::string line;
    while (std::getline(file, line)) {
        auto direction = line.at(0) == 'L' ? -1 : 1;
        auto clicks =  std::stoi(line.substr(1, line.length() - 1));
        currentPosition = abs(currentPosition + clicks * direction + 1000) % 100;
        if (currentPosition == 0) {
            zeroCount++;
        }
    }

    return zeroCount;
}


long solveDay01Part02() {
    auto zeroCount = 0L;
    auto currentPosition = 50;
    auto file = readInput(1);
    std::string line;
    while (std::getline(file, line)) {
        auto goingDown = line.at(0) == 'L';
        auto sign = goingDown ? -1 : 1;
        auto remainingClicks =  std::stoi(line.substr(1, line.length() - 1));

        do {
            auto clicksNeededToHitZero = goingDown ? (currentPosition == 0 ?  100 : currentPosition) : (100 - currentPosition);
            if (remainingClicks >= clicksNeededToHitZero) {
                currentPosition = (currentPosition + clicksNeededToHitZero * sign) % 100;
                remainingClicks -= clicksNeededToHitZero;
                zeroCount++;
            } else {
                currentPosition = abs(currentPosition + remainingClicks * sign + 100) % 100;
                remainingClicks = 0;
            }

        } while (remainingClicks > 0);
    }

    return zeroCount;
}
