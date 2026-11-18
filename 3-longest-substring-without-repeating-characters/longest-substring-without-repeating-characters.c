#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int lengthOfLongestSubstring(char* s) {
    // Direct-access table for all 128 standard ASCII characters, initialized to -1
    int lastSeen[128];
    memset(lastSeen, -1, sizeof(lastSeen));

    int maxLen = 0;
    int left = 0;

    for (int right = 0; s[right] != '\0'; right++) {
        unsigned char c = (unsigned char)s[right];

        // If the character was seen inside the current window [left, right],
        // jump 'left' directly past its previous occurrence
        if (lastSeen[c] >= left) {
            left = lastSeen[c] + 1;
        }

        // Update the latest index of character 'c' and track maximum window width
        lastSeen[c] = right;
        maxLen = MAX(maxLen, right - left + 1);
    }

    return maxLen;
}