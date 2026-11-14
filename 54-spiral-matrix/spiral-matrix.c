#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    if (matrixSize == 0 || matrixColSize[0] == 0) {
        *returnSize = 0;
        return NULL;
    }

    int rows = matrixSize;
    int cols = matrixColSize[0];
    int total = rows * cols;

    int* result = (int*)malloc(total * sizeof(int));
    *returnSize = total;

    int top = 0, bottom = rows - 1;
    int left = 0, right = cols - 1;
    int idx = 0;

    while (top <= bottom && left <= right) {
        // 1. Traverse from left to right along the top row
        for (int col = left; col <= right; col++) {
            result[idx++] = matrix[top][col];
        }
        top++;

        // 2. Traverse from top to bottom along the right column
        for (int row = top; row <= bottom; row++) {
            result[idx++] = matrix[row][right];
        }
        right--;

        // 3. Traverse from right to left along the bottom row (if rows remain)
        if (top <= bottom) {
            for (int col = right; col >= left; col--) {
                result[idx++] = matrix[bottom][col];
            }
            bottom--;
        }

        // 4. Traverse from bottom to top along the left column (if columns remain)
        if (left <= right) {
            for (int row = bottom; row >= top; row--) {
                result[idx++] = matrix[row][left];
            }
            left++;
        }
    }

    return result;
}