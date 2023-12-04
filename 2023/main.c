#include <stdio.h>
#include "solutions/01-trebuchet.h"
#include "solutions/02-cubes.h"
#include "solutions/03-gear.h"
#include "solutions/04-scratchcards.h"

int main() {

    printf("               --               \n");
    printf("             --*---             \n");
    printf("           -------*--           \n");
    printf("         ------*---*---         \n");
    printf("       ---O----------O---       \n");
    printf("     -------*---O-----*----     \n");
    printf("   ----O-----*------*--------   \n");
    printf(" ---------O------*----------*-- \n");
    printf("--------------------------------\n");
    printf("|     Advent of Code  2023     |\n");
    printf("|------------------------------|\n");
    printf("|    Problem 01  (Trebuchet)   |\n");
    printf("|------------------------------|\n");
    printf("|   I: %ld   |    II: %ld  |\n", solve01Part1(), solve01Part2());
    printf("|------------------------------|\n");
    printf("|  Problem 02 (Cube Conundrum) |\n");
    printf("|------------------------------|\n");
    printf("|   I: %ld    |    II: %ld  |\n", solve02Part1(), solve02Part2());
    printf("|------------------------------|\n");
    printf("|   Problem 03  (Gear Ratio)   |\n");
    printf("|------------------------------|\n");
    printf("|   I: %ld  | II: %ld  |\n", solve03Part1(), solve03Part2());
    printf("|------------------------------|\n");
    printf("|   Problem 04 (Scratchcards)  |\n");
    printf("|------------------------------|\n");
    printf("|   I: %ld   |  II: %ld  |\n", solve04Part1(), solve04Part2());
    printf("|------------------------------|\n");

    return 0;
}
