#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getRow(int rowIndex, int* returnSize) {
    int len = rowIndex + 1;
    *returnSize = len;

    int* row = (int*)malloc(len * sizeof(int));
    row[0] = 1;

    // Compute C(rowIndex, k) iteratively from C(rowIndex, k - 1)
    for (int k = 1; k <= rowIndex; k++) {
        row[k] = (int)((long)row[k - 1] * (rowIndex - k + 1) / k);
    }

    return row;
}