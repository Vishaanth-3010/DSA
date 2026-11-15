#include <stdlib.h>

// Helper macros for min and max
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Helper function to allocate and append a 2-element interval to the result
void appendInterval(int** result, int* returnColumnSizes, int* count, int start, int end) {
    result[*count] = (int*)malloc(2 * sizeof(int));
    result[*count][0] = start;
    result[*count][1] = end;
    returnColumnSizes[*count] = 2;
    (*count)++;
}

int** insert(int** intervals, int intervalsSize, int* intervalsColSize, int* newInterval, int newIntervalSize, int* returnSize, int** returnColumnSizes) {
    // Worst-case size is intervalsSize + 1 (if newInterval doesn't overlap with anything)
    int maxCapacity = intervalsSize + 1;
    int** result = (int**)malloc(maxCapacity * sizeof(int*));
    *returnColumnSizes = (int*)malloc(maxCapacity * sizeof(int));

    int count = 0;
    int i = 0;

    // 1. Add all intervals ending before newInterval starts (no overlap)
    while (i < intervalsSize && intervals[i][1] < newInterval[0]) {
        appendInterval(result, *returnColumnSizes, &count, intervals[i][0], intervals[i][1]);
        i++;
    }

    // 2. Merge all overlapping intervals with newInterval
    // Overlap exists as long as the current interval starts before or when newInterval ends
    int mergedStart = newInterval[0];
    int mergedEnd = newInterval[1];

    while (i < intervalsSize && intervals[i][0] <= mergedEnd) {
        mergedStart = MIN(mergedStart, intervals[i][0]);
        mergedEnd = MAX(mergedEnd, intervals[i][1]);
        i++;
    }
    appendInterval(result, *returnColumnSizes, &count, mergedStart, mergedEnd);

    // 3. Add all remaining intervals starting after newInterval ends
    while (i < intervalsSize) {
        appendInterval(result, *returnColumnSizes, &count, intervals[i][0], intervals[i][1]);
        i++;
    }

    *returnSize = count;
    return result;
}