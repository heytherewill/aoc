#include "../utilities/file.h"
#include <sstream>
#include <map>
#include <utility>
#include <set>

#define Grid std::map<int, std::map<int, char>>

static std::set<std::pair<int, int>> getAccessibleRolls(Grid grid, std::pair<int, int> gridSize) {
    std::set<std::pair<int, int>> accessibleRolls;

    for (auto currentLine = 0; currentLine < gridSize.first; currentLine++) {
        for (auto currentRow = 0; currentRow < gridSize.second; currentRow++) {
            const auto beingChecked = grid[currentLine][currentRow];
            if (beingChecked != '@') continue;

            auto rollCount = 0;
            const auto minLineBound = std::max(0, currentLine - 1);
            const auto maxLineBound = std::min(gridSize.first, currentLine + 1);
            const auto minRowBound = std::max(0, currentRow - 1);
            const auto maxRowBound = std::min(gridSize.second, currentRow + 1);
            for (auto lineToCheck = minLineBound; lineToCheck <= maxLineBound; lineToCheck++) {
                for (auto rowToCheck = minRowBound; rowToCheck <= maxRowBound; rowToCheck++) {
                    if (grid[lineToCheck][rowToCheck] == '@') {
                        rollCount++;
                    }
                }
            }

            if (rollCount <= 4) {
                accessibleRolls.insert(std::make_pair(currentLine, currentRow));
            }
        }
    }

    return accessibleRolls;
}

static std::pair<Grid, std::pair<int, int>> initializeGrid() {
    auto file = readInput(4);
    Grid grid;
    std::string line;
    int lineIndex = 0;
    int rowIndex = 0;
    while (std::getline(file, line)) {
        for (rowIndex = 0; rowIndex < line.length(); rowIndex++) {
            grid[lineIndex][rowIndex] = line.at(rowIndex);
        }

        lineIndex++;
    }

    return std::make_pair(grid, std::make_pair(lineIndex, rowIndex));
}

unsigned long solveDay04Part01() {
    auto [grid, gridSize] = initializeGrid();
    const auto accessibleRolls = getAccessibleRolls(grid, gridSize);
    return accessibleRolls.size();
}

long solveDay04Part02() {
    auto [grid, gridSize] = initializeGrid();
    auto totalRemovedRolls = 0;
    auto rollsRemovedInPass = 0;

    do {
        const auto rollsMarkedForDeletion = getAccessibleRolls(grid, gridSize);
        for (auto [line, row] : rollsMarkedForDeletion) {
            grid[line][row] = '.';
        }

        rollsRemovedInPass = rollsMarkedForDeletion.size();
        totalRemovedRolls += rollsRemovedInPass;
    } while (rollsRemovedInPass > 0);

    return totalRemovedRolls;
}