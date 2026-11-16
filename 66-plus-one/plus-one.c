#include <stdlib.h>
#include <string.h>

int* plusOne(int* digits, int digitsSize, int* returnSize) {
    // 1. Traverse from right to left to handle addition and carry propagation
    for (int i = digitsSize - 1; i >= 0; i--) {
        if (digits[i] < 9) {
            digits[i]++;
            
            // Allocate a clean copy of size digitsSize to return
            int* result = (int*)malloc(digitsSize * sizeof(int));
            memcpy(result, digits, digitsSize * sizeof(int));
            *returnSize = digitsSize;
            return result;
        }
        // Digit was 9: becomes 0 and carry continues to the next iteration
        digits[i] = 0;
    }

    // 2. Overflow case: all digits were 9 (e.g., [9, 9] -> [1, 0, 0])
    int newSize = digitsSize + 1;
    // calloc automatically initializes all elements to 0
    int* result = (int*)calloc(newSize, sizeof(int));
    result[0] = 1;
    *returnSize = newSize;

    return result;
}