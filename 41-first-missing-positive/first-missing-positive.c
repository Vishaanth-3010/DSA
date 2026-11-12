int firstMissingPositive(int* nums, int numsSize) {
    // 1. Place each number in its target index: value x goes to index x - 1
    for (int i = 0; i < numsSize; i++) {
        while (nums[i] > 0 && nums[i] <= numsSize && nums[nums[i] - 1] != nums[i]) {
            int targetIdx = nums[i] - 1;
            int temp = nums[i];
            nums[i] = nums[targetIdx];
            nums[targetIdx] = temp;
        }
    }

    // 2. Find the first index where the value does not match index + 1
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != i + 1) {
            return i + 1;
        }
    }

    // 3. All numbers from 1 to numsSize are present
    return numsSize + 1;
}