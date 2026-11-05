#include <string.h>

int strStr(char* haystack, char* needle) {
    int hLen = strlen(haystack);
    int nLen = strlen(needle);

    // If needle is longer than haystack, it can't exist inside it
    if (nLen > hLen) {
        return -1;
    }

    // Slide the window across haystack
    for (int i = 0; i <= hLen - nLen; i++) {
        int j = 0;

        // Check character by character
        while (j < nLen && haystack[i + j] == needle[j]) {
            j++;
        }

        // If all characters of needle matched
        if (j == nLen) {
            return i;
        }
    }

    // No match found
    return -1;
}