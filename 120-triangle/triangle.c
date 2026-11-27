static inline int min(int a, int b) {
    return (a < b) ? a : b;
}

int minimumTotal(int** triangle, int triangleSize, int* triangleColSize) {
    if (triangleSize == 0) return 0;

    // Work bottom-up from the second-to-last row to the top
    for (int row = triangleSize - 2; row >= 0; row--) {
        for (int col = 0; col <= row; col++) {
            triangle[row][col] += min(triangle[row + 1][col], triangle[row + 1][col + 1]);
        }
    }

    return triangle[0][0];
}