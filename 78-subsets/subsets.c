#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int totalSubsets = 1 << numsSize;
    *returnSize = totalSubsets;

    int** result = (int**)malloc(totalSubsets * sizeof(int*));
    *returnColumnSizes = (int*)malloc(totalSubsets * sizeof(int));

    for (int mask = 0; mask < totalSubsets; mask++) {
        // Count set bits to allocate the exact size needed for this subset
        int subsetLen = 0;
        for (int i = 0; i < numsSize; i++) {
            if (mask & (1 << i)) {
                subsetLen++;
            }
        }

        (*returnColumnSizes)[mask] = subsetLen;
        result[mask] = (int*)malloc(subsetLen * sizeof(int));

        // Populate the subset using the set bit positions
        int idx = 0;
        for (int i = 0; i < numsSize; i++) {
            if (mask & (1 << i)) {
                result[mask][idx++] = nums[i];
            }
        }
    }

    return result;
}