#include <stdbool.h>
#include <stdlib.h>

static inline unsigned int hashInt(int key, unsigned int mask) {
    // Mix bits (Murmur3 finalizer) to prevent clustering on sequential/negative keys
    unsigned int x = (unsigned int)key;
    x ^= x >> 16;
    x *= 0x85ebca6bU;
    x ^= x >> 13;
    x *= 0xc2b2ae35U;
    x ^= x >> 16;
    return x & mask;
}

int longestConsecutive(int* nums, int numsSize) {
    if (numsSize == 0) return 0;

    // Choose power-of-2 capacity >= 2 * numsSize (load factor <= 0.5)
    unsigned int cap = 16;
    while (cap < (unsigned int)numsSize * 2) {
        cap <<= 1;
    }
    unsigned int mask = cap - 1;

    int* keys = (int*)malloc(cap * sizeof(int));
    unsigned char* used = (unsigned char*)calloc(cap, sizeof(unsigned char));

    // 1. Insert all unique elements into the open-addressing hash set
    for (int i = 0; i < numsSize; i++) {
        int val = nums[i];
        unsigned int idx = hashInt(val, mask);
        while (used[idx]) {
            if (keys[idx] == val) break; // Duplicate key
            idx = (idx + 1) & mask;
        }
        if (!used[idx]) {
            used[idx] = 1;
            keys[idx] = val;
        }
    }

    int longest = 0;

    // 2. Scan unique keys; expand only from sequence start points (val - 1 not present)
    for (unsigned int i = 0; i < cap; i++) {
        if (!used[i]) continue;

        int start = keys[i];

        // Check if (start - 1) exists in the hash set
        int prev = start - 1;
        unsigned int pIdx = hashInt(prev, mask);
        bool hasPrev = false;
        while (used[pIdx]) {
            if (keys[pIdx] == prev) {
                hasPrev = true;
                break;
            }
            pIdx = (pIdx + 1) & mask;
        }
        if (hasPrev) continue;

        // Expand forward while (curr + 1) exists
        int curr = start;
        int streak = 1;
        while (true) {
            int next = curr + 1;
            unsigned int nIdx = hashInt(next, mask);
            bool foundNext = false;
            while (used[nIdx]) {
                if (keys[nIdx] == next) {
                    foundNext = true;
                    break;
                }
                nIdx = (nIdx + 1) & mask;
            }
            if (!foundNext) break;
            curr = next;
            streak++;
        }

        if (streak > longest) {
            longest = streak;
        }
    }

    free(keys);
    free(used);
    return longest;
}