#include <stdlib.h>

#define parseLong(numberString) strtol(numberString, NULL, 10)

#define max(x, y) (x > y ? x : y)
#define min(x, y) (x < y ? x : y)

int countNumberOfDigitsInNumber(int number);

long gcd(long a, long b);
long lcm(long a, long b);
long lcmForArray(long *array, int arrayLength);