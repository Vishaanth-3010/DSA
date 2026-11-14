#include <stdio.h>

int maxSubArray(int* nums, int numsSize) {
    int max_so_far = nums[0];
    int current_max = nums[0];

    for (int i = 1; i < numsSize; i++) {
        // Either extend the existing subarray or start a new one at nums[i]
        if (current_max + nums[i] > nums[i]) {
            current_max = current_max + nums[i];
        } else {
            current_max = nums[i];
        }

        // Update the global maximum if the current subarray sum is larger
        if (current_max > max_so_far) {
            max_so_far = current_max;
        }
    }

    return max_so_far;
}