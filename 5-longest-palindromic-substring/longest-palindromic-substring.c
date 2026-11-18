#include <stdlib.h>
#include <string.h>

// Helper function that expands outward from [left, right] while characters match,
// returning the length of the longest palindrome centered there.
int expandAroundCenter(const char* s, int n, int left, int right) {
    while (left >= 0 && right < n && s[left] == s[right]) {
        left--;
        right++;
    }
    // After the loop terminates, left and right are one step past the valid bounds:
    // length = (right - 1) - (left + 1) + 1 = right - left - 1
    return right - left - 1;
}

char* longestPalindrome(char* s) {
    int n = strlen(s);
    if (n == 0) {
        char* empty = (char*)malloc(1);
        empty[0] = '\0';
        return empty;
    }

    int start = 0;
    int maxLen = 1;

    for (int i = 0; i < n; i++) {
        // 1. Odd-length palindrome centered at index i
        int len1 = expandAroundCenter(s, n, i, i);
        // 2. Even-length palindrome centered between i and i + 1
        int len2 = expandAroundCenter(s, n, i, i + 1);

        int len = (len1 > len2) ? len1 : len2;

        // Update best substring bounds if a longer palindrome is found
        if (len > maxLen) {
            maxLen = len;
            // Calculate starting index from center i and palindrome length
            start = i - (len - 1) / 2;
        }
    }

    // Allocate exact buffer (+1 for null terminator) and copy the substring
    char* result = (char*)malloc((maxLen + 1) * sizeof(char));
    memcpy(result, s + start, maxLen);
    result[maxLen] = '\0';

    return result;
}