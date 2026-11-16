#include <stdlib.h>
#include <string.h>

char** fullJustify(char** words, int wordsSize, int maxWidth, int* returnSize) {
    // Worst case: every word sits on its own line
    char** result = (char**)malloc(wordsSize * sizeof(char*));
    int lineCount = 0;

    // Pre-cache word lengths to avoid repeated strlen calls
    int* wordLens = (int*)malloc(wordsSize * sizeof(int));
    for (int k = 0; k < wordsSize; k++) {
        wordLens[k] = strlen(words[k]);
    }

    int i = 0;
    while (i < wordsSize) {
        // 1. Greedily determine the range of words [i, j - 1] that fit on this line
        int lineWordsLen = wordLens[i];
        int j = i + 1;

        while (j < wordsSize && (lineWordsLen + 1 + wordLens[j]) <= maxWidth) {
            lineWordsLen += 1 + wordLens[j]; // +1 accounts for mandatory single space
            j++;
        }

        int numWords = j - i;
        int totalChars = 0;
        for (int k = i; k < j; k++) {
            totalChars += wordLens[k];
        }
        int totalSpaces = maxWidth - totalChars;

        // Allocate line buffer (+1 for null terminator)
        char* line = (char*)malloc((maxWidth + 1) * sizeof(char));
        int pos = 0;

        // 2. Format the line:
        // Case A: Last line OR only one word on the line -> Left-justified
        if (j == wordsSize || numWords == 1) {
            for (int k = i; k < j; k++) {
                memcpy(line + pos, words[k], wordLens[k]);
                pos += wordLens[k];
                if (k < j - 1) {
                    line[pos++] = ' ';
                }
            }
            // Pad remaining width on the right with spaces
            while (pos < maxWidth) {
                line[pos++] = ' ';
            }
        } 
        // Case B: Standard middle line with multiple words -> Full-justified
        else {
            int gaps = numWords - 1;
            int baseSpaces = totalSpaces / gaps;
            int extraSpaces = totalSpaces % gaps; // Distributed one per gap from the left

            for (int k = i; k < j; k++) {
                memcpy(line + pos, words[k], wordLens[k]);
                pos += wordLens[k];

                if (k < j - 1) {
                    int spacesToAdd = baseSpaces + ((k - i) < extraSpaces ? 1 : 0);
                    memset(line + pos, ' ', spacesToAdd);
                    pos += spacesToAdd;
                }
            }
        }

        line[maxWidth] = '\0';
        result[lineCount++] = line;
        i = j; // Advance to the first word of the next line
    }

    free(wordLens);
    *returnSize = lineCount;
    return result;
}