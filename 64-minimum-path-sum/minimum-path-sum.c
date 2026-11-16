#include <stdlib.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int minPathSum(int** grid, int gridSize, int* gridColSize) {
    int rows = gridSize;
    int cols = gridColSize[0];

    // Allocate a 1D DP array to store the running minimum path sum per column
    int* dp = (int*)malloc(cols * sizeof(int));

    // 1. Initialize the starting cell
    dp[0] = grid[0][0];

    // 2. Initialize the first row (can only arrive from the left)
    for (int j = 1; j < cols; j++) {
        dp[j] = dp[j - 1] + grid[0][j];
    }

    // 3. Process remaining rows
    for (int i = 1; i < rows; i++) {
        // First column in each row can only arrive from directly above
        dp[0] += grid[i][0];

        // Remaining cells take the minimum of top (dp[j]) and left (dp[j - 1])
        for (int j = 1; j < cols; j++) {
            dp[j] = grid[i][j] + MIN(dp[j], dp[j - 1]);
        }
    }

    int result = dp[cols - 1];
    free(dp); // Prevent memory leaks

    return result;
}