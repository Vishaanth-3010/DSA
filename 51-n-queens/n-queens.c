#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void backtrack(
    int row,
    int n,
    int* queens,          // queens[r] = column index of queen in row r
    bool* cols,
    bool* diag1,          // row - col + n - 1
    bool* diag2,          // row + col
    char**** results,
    int* returnSize,
    int* capacity
) {
    if (row == n) {
        // Resize results array dynamically if needed
        if (*returnSize >= *capacity) {
            *capacity *= 2;
            *results = (char***)realloc(*results, (*capacity) * sizeof(char**));
        }

        // Build the n x n board for this valid solution
        char** board = (char**)malloc(n * sizeof(char*));
        for (int r = 0; r < n; r++) {
            board[r] = (char*)malloc((n + 1) * sizeof(char));
            memset(board[r], '.', n);
            board[r][queens[r]] = 'Q';
            board[r][n] = '\0';
        }

        (*results)[*returnSize] = board;
        (*returnSize)++;
        return;
    }

    for (int col = 0; col < n; col++) {
        int d1 = row - col + n - 1;
        int d2 = row + col;

        // Skip if column or either diagonal is already attacked
        if (cols[col] || diag1[d1] || diag2[d2]) {
            continue;
        }

        // Place queen
        queens[row] = col;
        cols[col] = diag1[d1] = diag2[d2] = true;

        // Recurse to next row
        backtrack(row + 1, n, queens, cols, diag1, diag2, results, returnSize, capacity);

        // Backtrack (remove queen)
        cols[col] = diag1[d1] = diag2[d2] = false;
    }
}

char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    int capacity = 16;
    char*** results = (char***)malloc(capacity * sizeof(char**));

    int* queens = (int*)malloc(n * sizeof(int));
    bool* cols = (bool*)calloc(n, sizeof(bool));
    bool* diag1 = (bool*)calloc(2 * n - 1, sizeof(bool));
    bool* diag2 = (bool*)calloc(2 * n - 1, sizeof(bool));

    backtrack(0, n, queens, cols, diag1, diag2, &results, returnSize, &capacity);

    // Populate returnColumnSizes (every solution has n rows)
    *returnColumnSizes = (int*)malloc((*returnSize) * sizeof(int));
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = n;
    }

    // Free temporary tracking arrays
    free(queens);
    free(cols);
    free(diag1);
    free(diag2);

    return results;
}