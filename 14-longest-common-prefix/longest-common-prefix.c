#include <stdlib.h>
#include <string.h>
char* longestCommonPrefix(char** strs, int strsSize) {
    if (strsSize == 0) return "";

    int len = strlen(strs[0]);
    char* prefix = (char*)malloc((len + 1) * sizeof(char));

    for (int i = 0; i < len; i++) {
        char ch = strs[0][i];

        for (int j = 1; j < strsSize; j++) {
            // Stop if current string ends or characters don't match
            if (strs[j][i] == '\0' || strs[j][i] != ch) {
                prefix[i] = '\0';
                return prefix;
            }
        }
        prefix[i] = ch;
    }
    prefix[len] = '\0';
    return prefix;
}