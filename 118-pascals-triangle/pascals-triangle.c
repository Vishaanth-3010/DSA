#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generate(int numRows, int* returnSize, int** returnColumnSizes) {
    *returnSize = numRows;
    int** triangle = (int**)malloc(numRows * sizeof(int*));
    *returnColumnSizes = (int*)malloc(numRows * sizeof(int));

    for (int i = 0; i < numRows; i++) {
        int rowLen = i + 1;
        (*returnColumnSizes)[i] = rowLen;
        triangle[i] = (int*)malloc(rowLen * sizeof(int));

        // First and last elements of every row are always 1
        triangle[i][0] = 1;
        triangle[i][rowLen - 1] = 1;

        // Fill interior elements using the sum of the two parents above
        for (int j = 1; j < rowLen - 1; j++) {
            triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }
    }

    return triangle;
}