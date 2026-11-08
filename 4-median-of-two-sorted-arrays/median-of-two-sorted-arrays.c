#include <limits.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    // Ensure nums1 is the smaller array to minimize binary search range
    if (nums1Size > nums2Size) {
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    }

    int m = nums1Size;
    int n = nums2Size;
    int low = 0, high = m;

    while (low <= high) {
        int i = low + (high - low) / 2;       // Partition index for nums1
        int j = (m + n + 1) / 2 - i;          // Partition index for nums2

        int maxLeft1  = (i == 0) ? INT_MIN : nums1[i - 1];
        int minRight1 = (i == m) ? INT_MAX : nums1[i];

        int maxLeft2  = (j == 0) ? INT_MIN : nums2[j - 1];
        int minRight2 = (j == n) ? INT_MAX : nums2[j];

        if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {
            // Correct partition found
            if ((m + n) % 2 == 0) {
                return (MAX(maxLeft1, maxLeft2) + MIN(minRight1, minRight2)) / 2.0;
            } else {
                return (double)MAX(maxLeft1, maxLeft2);
            }
        } else if (maxLeft1 > minRight2) {
            high = i - 1; // Move partition left in nums1
        } else {
            low = i + 1;  // Move partition right in nums1
        }
    }

    return 0.0; // Unreachable for valid sorted inputs
}