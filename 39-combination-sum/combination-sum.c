#include <stdlib.h>

int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void backtrack(int* candidates, int candidatesSize, int target, int start,
               int* current, int currLen,
               int*** res, int* returnSize, int** returnColumnSizes, int* capacity) {
    if (target == 0) {
        if (*returnSize == *capacity) {
            *capacity *= 2;
            *res = (int**)realloc(*res, sizeof(int*) * (*capacity));
            *returnColumnSizes = (int*)realloc(*returnColumnSizes, sizeof(int) * (*capacity));
        }

        int* comb = (int*)malloc(sizeof(int) * currLen);
        for (int i = 0; i < currLen; i++) {
            comb[i] = current[i];
        }

        (*res)[*returnSize] = comb;
        (*returnColumnSizes)[*returnSize] = currLen;
        (*returnSize)++;
        return;
    }

    for (int i = start; i < candidatesSize; i++) {
        // Prune: since candidates are sorted, no need to check larger numbers
        if (candidates[i] > target) {
            break;
        }

        current[currLen] = candidates[i];
        // Pass 'i' (not 'i + 1') because the same number can be reused
        backtrack(candidates, candidatesSize, target - candidates[i], i,
                  current, currLen + 1, res, returnSize, returnColumnSizes, capacity);
    }
}

int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    qsort(candidates, candidatesSize, sizeof(int), cmp);

    int capacity = 16;
    *returnSize = 0;
    int** res = (int**)malloc(sizeof(int*) * capacity);
    *returnColumnSizes = (int*)malloc(sizeof(int) * capacity);

    // Max depth of recursion is at most 'target' (assuming positive candidates)
    int* current = (int*)malloc(sizeof(int) * (target + 1));

    backtrack(candidates, candidatesSize, target, 0, current, 0,
              &res, returnSize, returnColumnSizes, &capacity);

    free(current);
    return res;
}