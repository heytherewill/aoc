#include "../utilities/file.h"
#include <sstream>

long solveDay02Part01() {
    auto sumOfInvalidIds = 0L;

    auto file = readInput(2);
    std::string line;
    std::string range;
    std::getline(file, line);
    std::stringstream input(line);

    while(std::getline(input, range, ',')) {
        auto indexOfSeparator = range.find('-');
        auto start = std::stol(range.substr(0, indexOfSeparator));
        auto end = std::stol(range.substr(indexOfSeparator + 1, range.size()));
        for(auto id = start; id <= end; id++) {
            std::string number = std::to_string(id);
            auto numberLength = number.length();
            if (numberLength % 2 == 0) {
                auto idSegmentLength = numberLength / 2;
                auto potentialSequence = number.substr(0, idSegmentLength);
                if (number.substr(idSegmentLength, idSegmentLength) == potentialSequence) {
                    sumOfInvalidIds += id;
                }
            }
        }
    }

    return sumOfInvalidIds;
}

long solveDay02Part02() {
    auto sumOfInvalidIds = 0L;

    auto file = readInput(2);
    std::string line;
    std::string range;
    std::getline(file, line);
    std::stringstream input(line);

    while(std::getline(input, range, ',')) {
        auto indexOfSeparator = range.find('-');
        auto start = std::stol(range.substr(0, indexOfSeparator));
        auto end = std::stol(range.substr(indexOfSeparator + 1, range.size()));
        for(auto id = start; id <= end; id++) {
            std::string number = std::to_string(id);
            auto numberLength = number.length();
            auto maxIdSegment = numberLength / 2;
            bool isMatch;
            auto idSegmentLength = 1;
            do {
                if (numberLength % idSegmentLength == 0) {
                    auto potentialSequence = number.substr(0, idSegmentLength);
                    auto currentStartingPoint = idSegmentLength;
                    do {
                        isMatch = number.substr(currentStartingPoint, idSegmentLength) == potentialSequence;
                        currentStartingPoint += idSegmentLength;
                    } while(isMatch && currentStartingPoint < numberLength);

                    if (isMatch) {
                        sumOfInvalidIds += id;
                    }
                }
                idSegmentLength++;
            } while (!isMatch && idSegmentLength <= maxIdSegment);
        }
    }

    return sumOfInvalidIds;
}