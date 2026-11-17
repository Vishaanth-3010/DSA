#include <stdlib.h>
#include <string.h>

// Comparator for qsort to sort integers in ascending order
int compareInts(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

void backtrack(int* nums, int numsSize, int start, int* path, int pathLen,
               int** result, int* returnColumnSizes, int* count) {
    // 1. Record the current subset (even if empty)
    result[*count] = (int*)malloc(pathLen * sizeof(int));
    if (pathLen > 0) {
        memcpy(result[*count], path, pathLen * sizeof(int));
    }
    returnColumnSizes[*count] = pathLen;
    (*count)++;

    // 2. Explore further elements
    for (int i = start; i < numsSize; i++) {
        // Skip duplicates at the same recursion tree level
        if (i > start && nums[i] == nums[i - 1]) {
            continue;
        }

        path[pathLen] = nums[i];
        backtrack(nums, numsSize, i + 1, path, pathLen + 1, result, returnColumnSizes, count);
    }
}

int** subsetsWithDup(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    // 1. Sort input so duplicates sit next to each other
    qsort(nums, numsSize, sizeof(int), compareInts);

    // Maximum possible subsets for N elements is 2^N
    int maxSubsets = 1 << numsSize;
    int** result = (int**)malloc(maxSubsets * sizeof(int*));
    *returnColumnSizes = (int*)malloc(maxSubsets * sizeof(int));

    // Temporary buffer holding the active subset along the recursion stack
    int* path = (int*)malloc(numsSize * sizeof(int));
    int count = 0;

    // 2. Generate all unique subsets via DFS backtracking
    backtrack(nums, numsSize, 0, path, 0, result, *returnColumnSizes, &count);

    free(path);
    *returnSize = count;
    return result;
}