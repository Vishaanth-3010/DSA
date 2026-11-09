#include <stdbool.h>

bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    // Trackers for digits 1-9 (mapped to indices 0-8)
    bool rows[9][9] = {false};
    bool cols[9][9] = {false};
    bool boxes[9][9] = {false};

    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (board[r][c] == '.') {
                continue; // Skip empty cells
            }

            // Convert '1'-'9' into 0-8 index
            int num = board[r][c] - '1';

            // Map (r, c) to one of the nine 3x3 boxes (0 to 8)
            int boxIndex = (r / 3) * 3 + (c / 3);

            // If already seen in the current row, column, or box, it's invalid
            if (rows[r][num] || cols[c][num] || boxes[boxIndex][num]) {
                return false;
            }

            // Mark the number as seen
            rows[r][num] = true;
            cols[c][num] = true;
            boxes[boxIndex][num] = true;
        }
    }

    return true;
}