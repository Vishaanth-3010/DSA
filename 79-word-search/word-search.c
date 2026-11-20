#include <stdbool.h>
#include <string.h>

static bool dfs(char** board, int m, int n, int r, int c, const char* word, int idx) {
    // Base case: all characters matched
    if (word[idx] == '\0') return true;

    // Boundary check and character mismatch check
    if (r < 0 || r >= m || c < 0 || c >= n || board[r][c] != word[idx]) {
        return false;
    }

    // Mark current cell as visited in-place
    char temp = board[r][c];
    board[r][c] = '#';

    // Explore 4 adjacent directions
    bool found = dfs(board, m, n, r + 1, c, word, idx + 1) ||
                 dfs(board, m, n, r - 1, c, word, idx + 1) ||
                 dfs(board, m, n, r, c + 1, word, idx + 1) ||
                 dfs(board, m, n, r, c - 1, word, idx + 1);

    // Backtrack: restore original character
    board[r][c] = temp;

    return found;
}

bool exist(char** board, int boardSize, int* boardColSize, char* word) {
    if (boardSize == 0 || boardColSize[0] == 0) return false;

    int m = boardSize;
    int n = boardColSize[0];
    int wordLen = strlen(word);

    // Pruning 1: Word cannot fit if it has more characters than total board cells
    if (wordLen > m * n) return false;

    // Pruning 2: Frequency check to fail fast on impossible words
    int boardFreq[128] = {0};
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            boardFreq[(unsigned char)board[i][j]]++;
        }
    }
    for (int k = 0; k < wordLen; k++) {
        if (--boardFreq[(unsigned char)word[k]] < 0) {
            return false;
        }
    }

    // Launch DFS from every cell matching word[0]
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == word[0] && dfs(board, m, n, i, j, word, 0)) {
                return true;
            }
        }
    }

    return false;
}