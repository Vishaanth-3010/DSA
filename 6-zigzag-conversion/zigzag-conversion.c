#include <stdlib.h>
#include <string.h>

char* convert(char* s, int numRows) {
    int n = strlen(s);

    // Edge case: 1 row or string shorter than numRows produces no zigzag
    if (numRows <= 1 || numRows >= n) {
        char* result = (char*)malloc((n + 1) * sizeof(char));
        memcpy(result, s, n + 1); // Copies string including '\0'
        return result;
    }

    char* result = (char*)malloc((n + 1) * sizeof(char));
    int writeIdx = 0;

    // A full downward-and-diagonal cycle spans (2 * numRows - 2) characters
    int cycleLen = 2 * numRows - 2;

    for (int row = 0; row < numRows; row++) {
        for (int j = row; j < n; j += cycleLen) {
            // 1. Append the vertical column character for the current cycle
            result[writeIdx++] = s[j];

            // 2. For middle rows (not top or bottom), also append the diagonal character
            int diagIdx = j + cycleLen - 2 * row;
            if (row > 0 && row < numRows - 1 && diagIdx < n) {
                result[writeIdx++] = s[diagIdx];
            }
        }
    }

    result[n] = '\0';
    return result;
}