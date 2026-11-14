#include <stdbool.h>

bool canJump(int* nums, int numsSize) {
    int max_reach = 0;

    for (int i = 0; i < numsSize; i++) {
        // If the current index is beyond the furthest reachable point, we're stuck
        if (i > max_reach) {
            return false;
        }

        // Update the furthest index we can reach from here
        if (i + nums[i] > max_reach) {
            max_reach = i + nums[i];
        }

        // Early exit if we can already reach or pass the last index
        if (max_reach >= numsSize - 1) {
            return true;
        }
    }

    return true;
}