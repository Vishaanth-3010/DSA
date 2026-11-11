#include <limits.h>
#include <stdlib.h>

int divide(int dividend, int divisor) {
    // Handle overflow edge case
    if (dividend == INT_MIN && divisor == -1) {
        return INT_MAX;
    }

    // Determine the sign of the result
    int isNegative = (dividend < 0) ^ (divisor < 0);

    // Work with positive long long values to avoid overflow
    long long dvd = llabs((long long)dividend);
    long long dvs = llabs((long long)divisor);
    long long quotient = 0;

    while (dvd >= dvs) {
        long long temp = dvs;
        long long multiple = 1;

        // Double temp until it's just under dvd
        while (dvd >= (temp << 1)) {
            temp <<= 1;
            multiple <<= 1;
        }

        dvd -= temp;
        quotient += multiple;
    }

    return isNegative ? (int)-quotient : (int)quotient;
}