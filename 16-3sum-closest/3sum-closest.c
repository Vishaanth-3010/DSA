#include <stdlib.h>

// Place outside threeSumClosest
static int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int threeSumClosest(int* nums, int numsSize, int target) {
    // Sort array to enable two-pointer traversal
    qsort(nums, numsSize, sizeof(int), compare);

    int closest_sum = nums[0] + nums[1] + nums[2];

    for (int i = 0; i < numsSize - 2; i++) {
        // Skip duplicate base values to avoid redundant windows
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }

        int left = i + 1;
        int right = numsSize - 1;

        while (left < right) {
            int current_sum = nums[i] + nums[left] + nums[right];

            // Exact match is optimal
            if (current_sum == target) {
                return current_sum;
            }

            // Update closest_sum if current difference is strictly smaller
            if (abs(current_sum - target) < abs(closest_sum - target)) {
                closest_sum = current_sum;
            }

            if (current_sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }

    return closest_sum;
}