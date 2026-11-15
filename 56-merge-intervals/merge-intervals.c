#include <stdlib.h>

// Comparator function for qsort to sort intervals by their start time
int compareIntervals(const void* a, const void* b) {
    int* intervalA = *(int**)a;
    int* intervalB = *(int**)b;
    
    // Avoid integer overflow compared to (intervalA[0] - intervalB[0])
    if (intervalA[0] < intervalB[0]) return -1;
    if (intervalA[0] > intervalB[0]) return 1;
    return 0;
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {
    if (intervalsSize == 0) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    // 1. Sort the intervals based on the start time
    qsort(intervals, intervalsSize, sizeof(int*), compareIntervals);

    // 2. Allocate memory for the worst-case scenario (no intervals overlap)
    int** merged = (int**)malloc(intervalsSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(intervalsSize * sizeof(int));
    
    int count = 0; // Tracks the number of merged intervals

    // 3. Initialize the first interval in the result array
    merged[0] = (int*)malloc(2 * sizeof(int));
    merged[0][0] = intervals[0][0];
    merged[0][1] = intervals[0][1];
    (*returnColumnSizes)[0] = 2;
    count++;

    // 4. Iterate through the rest of the intervals
    for (int i = 1; i < intervalsSize; i++) {
        int currentStart = intervals[i][0];
        int currentEnd = intervals[i][1];
        int lastMergedEnd = merged[count - 1][1];

        if (currentStart <= lastMergedEnd) {
            // Overlap detected: extend the end of the previous merged interval if needed
            if (currentEnd > lastMergedEnd) {
                merged[count - 1][1] = currentEnd;
            }
        } else {
            // No overlap: allocate and append a new interval
            merged[count] = (int*)malloc(2 * sizeof(int));
            merged[count][0] = currentStart;
            merged[count][1] = currentEnd;
            (*returnColumnSizes)[count] = 2;
            count++;
        }
    }

    // 5. Set the final return size
    *returnSize = count;
    return merged;
}