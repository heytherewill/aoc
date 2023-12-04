int countNumberOfDigitsInNumber(int number) {
    int result = 0;
    do {
        number /= 10;
        result++;
    } while (number != 0);

    return result;
}