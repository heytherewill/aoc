#include <iostream>
#include <fstream>
#include "solutions/solutions.h"

int main() {
    std::cout << "                -                " << std::endl;
    std::cout << "               ---               " << std::endl;
    std::cout << "             --*----             " << std::endl;
    std::cout << "           -------*---           " << std::endl;
    std::cout << "         ------*---*----         " << std::endl;
    std::cout << "       ---O----------O----       " << std::endl;
    std::cout << "     -------*---O-----*-----     " << std::endl;
    std::cout << "   ----O-----*------*---------   " << std::endl;
    std::cout << " ---------O------*-----------*-- " << std::endl;
    std::cout << "---------------------------------" << std::endl;
    std::cout << "|     Advent of Code   2025     |" << std::endl;
    std::cout << "|-------------------------------|" << std::endl;
    std::cout << "| Problem 01  (Secret Entrance) |" << std::endl;
    std::cout << "|-------------------------------|" << std::endl;
    std::cout << "|   I: " << solveDay01Part01() << "    |    II: " << solveDay01Part02() << "  |\n" << std::endl;
    std::cout << "|-------------------------------|" << std::endl;
    std::cout << "|    Problem  02 (Gift Shop)    |" << std::endl;
    std::cout << "|-------------------------------|" << std::endl;
    std::cout << "|   I: " << solveDay02Part01() << "    |    II: " << solveDay02Part02() << "  |\n" << std::endl;
    return 0;
}
