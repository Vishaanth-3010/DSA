#include <stdbool.h>

bool backtrack(char** board, int r, int c, int* rows, int* cols, int* boxes) {
    if (r == 9) {
        return true;
    }

    int next_r = (c == 8) ? r + 1 : r;
    int next_c = (c == 8) ? 0 : c + 1;

    if (board[r][c] != '.') {
        return backtrack(board, next_r, next_c, rows, cols, boxes);
    }

    int box_idx = (r / 3) * 3 + (c / 3);
    int used = rows[r] | cols[c] | boxes[box_idx];

    for (int d = 0; d < 9; d++) {
        int mask = 1 << d;
        if (!(used & mask)) {
            board[r][c] = '1' + d;
            rows[r] |= mask;
            cols[c] |= mask;
            boxes[box_idx] |= mask;

            if (backtrack(board, next_r, next_c, rows, cols, boxes)) {
                return true;
            }

            // Backtrack
            board[r][c] = '.';
            rows[r] &= ~mask;
            cols[c] &= ~mask;
            boxes[box_idx] &= ~mask;
        }
    }

    return false;
}

void solveSudoku(char** board, int boardSize, int* boardColSize) {
    int rows[9] = {0};
    int cols[9] = {0};
    int boxes[9] = {0};

    // Initialize bitmasks with the starting board state
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (board[r][c] != '.') {
                int mask = 1 << (board[r][c] - '1');
                rows[r] |= mask;
                cols[c] |= mask;
                boxes[(r / 3) * 3 + (c / 3)] |= mask;
            }
        }
    }

    backtrack(board, 0, 0, rows, cols, boxes);
}