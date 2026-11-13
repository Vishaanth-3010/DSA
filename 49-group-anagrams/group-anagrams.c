#include <stdlib.h>
#include <string.h>

typedef struct {
    char* sorted;
    char* original;
} WordPair;

// Comparator for sorting characters within a single word
int cmpChar(const void* a, const void* b) {
    return (*(const char*)a - *(const char*)b);
}

// Comparator for sorting WordPairs by their canonical sorted string
int cmpPair(const void* a, const void* b) {
    const WordPair* pa = (const WordPair*)a;
    const WordPair* pb = (const WordPair*)b;
    return strcmp(pa->sorted, pb->sorted);
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    if (strsSize == 0) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    // 1. Create pairs of (sorted_key, original_string)
    WordPair* pairs = (WordPair*)malloc(strsSize * sizeof(WordPair));
    for (int i = 0; i < strsSize; i++) {
        int len = strlen(strs[i]);
        pairs[i].sorted = (char*)malloc((len + 1) * sizeof(char));
        strcpy(pairs[i].sorted, strs[i]);
        qsort(pairs[i].sorted, len, sizeof(char), cmpChar);
        pairs[i].original = strs[i];
    }

    // 2. Sort all pairs by their canonical sorted key so anagrams become adjacent
    qsort(pairs, strsSize, sizeof(WordPair), cmpPair);

    // 3. Allocate result arrays (at most strsSize groups)
    char*** result = (char***)malloc(strsSize * sizeof(char**));
    *returnColumnSizes = (int*)malloc(strsSize * sizeof(int));
    int groupCount = 0;

    // 4. Sweep through sorted pairs and collect adjacent matches into groups
    int i = 0;
    while (i < strsSize) {
        int j = i + 1;
        while (j < strsSize && strcmp(pairs[i].sorted, pairs[j].sorted) == 0) {
            j++;
        }

        int groupSize = j - i;
        result[groupCount] = (char**)malloc(groupSize * sizeof(char*));
        (*returnColumnSizes)[groupCount] = groupSize;

        for (int k = 0; k < groupSize; k++) {
            // Allocate and copy string so caller owns all memory safely
            result[groupCount][k] = (char*)malloc((strlen(pairs[i + k].original) + 1) * sizeof(char));
            strcpy(result[groupCount][k], pairs[i + k].original);
        }

        groupCount++;
        i = j;
    }

    // 5. Clean up temporary helper memory
    for (int k = 0; k < strsSize; k++) {
        free(pairs[k].sorted);
    }
    free(pairs);

    *returnSize = groupCount;
    return result;
}