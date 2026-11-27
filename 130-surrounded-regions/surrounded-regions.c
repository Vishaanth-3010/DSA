static void markSafe(char** board, int m, int n, int r, int c) {
    if (r < 0 || r >= m || c < 0 || c >= n || board[r][c] != 'O') {
        return;
    }

    board[r][c] = '#';

    markSafe(board, m, n, r + 1, c);
    markSafe(board, m, n, r - 1, c);
    markSafe(board, m, n, r, c + 1);
    markSafe(board, m, n, r, c - 1);
}

void solve(char** board, int boardSize, int* boardColSize) {
    if (boardSize <= 2 || boardColSize[0] <= 2) return;

    int m = boardSize;
    int n = boardColSize[0];

    // 1. Traverse left and right borders to mark border-connected 'O's as '#'
    for (int i = 0; i < m; i++) {
        if (board[i][0] == 'O') markSafe(board, m, n, i, 0);
        if (board[i][n - 1] == 'O') markSafe(board, m, n, i, n - 1);
    }

    // 2. Traverse top and bottom borders (excluding corners already checked)
    for (int j = 1; j < n - 1; j++) {
        if (board[0][j] == 'O') markSafe(board, m, n, 0, j);
        if (board[m - 1][j] == 'O') markSafe(board, m, n, m - 1, j);
    }

    // 3. Flip captured 'O' -> 'X' and restore safe '#' -> 'O'
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 'O') {
                board[i][j] = 'X';
            } else if (board[i][j] == '#') {
                board[i][j] = 'O';
            }
        }
    }
}