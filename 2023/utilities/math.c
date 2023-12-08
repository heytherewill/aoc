int countNumberOfDigitsInNumber(int number) {
    int result = 0;
    do {
        number /= 10;
        result++;
    } while (number != 0);

    return result;
}

long gcd(long a, long b) {
    while (b != 0) {
        long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long lcm(long a, long b) {
    return (a * b) / gcd(a, b);
}

long lcmForArray(long *array, int arrayLength) {
    long result = array[0];
    for (int i = 1; i < arrayLength; i++) {
        result = lcm(result, array[i]);
    }

    return result;
}
