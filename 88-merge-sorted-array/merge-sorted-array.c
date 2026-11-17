void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    int p1 = m - 1;          // Pointer to the last valid element in nums1
    int p2 = n - 1;          // Pointer to the last element in nums2
    int writeIdx = m + n - 1; // Pointer to the end of nums1's total buffer

    // Compare elements from the back and place the larger one at writeIdx
    while (p1 >= 0 && p2 >= 0) {
        if (nums1[p1] > nums2[p2]) {
            nums1[writeIdx--] = nums1[p1--];
        } else {
            nums1[writeIdx--] = nums2[p2--];
        }
    }

    // If any elements remain in nums2, copy them over.
    // (No need to check p1 >= 0, as remaining nums1 elements are already in place.)
    while (p2 >= 0) {
        nums1[writeIdx--] = nums2[p2--];
    }
}