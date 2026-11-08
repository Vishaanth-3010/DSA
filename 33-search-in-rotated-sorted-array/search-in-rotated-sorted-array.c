int search(int* nums, int numsSize, int target) {
    int low = 0;
    int high = numsSize - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (nums[mid] == target) {
            return mid;
        }

        // Check if the left half is sorted
        if (nums[low] <= nums[mid]) {
            if (target >= nums[low] && target < nums[mid]) {
                high = mid - 1; // Target is in the sorted left half
            } else {
                low = mid + 1;  // Target is in the right half
            }
        } 
        // Otherwise, the right half is sorted
        else {
            if (target > nums[mid] && target <= nums[high]) {
                low = mid + 1;  // Target is in the sorted right half
            } else {
                high = mid - 1; // Target is in the left half
            }
        }
    }

    return -1;
}