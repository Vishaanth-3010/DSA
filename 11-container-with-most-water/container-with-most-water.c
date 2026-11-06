int maxArea(int* height, int heightSize) {
    int left = 0;
    int right = heightSize - 1;
    int max_water = 0;

    while (left < right) {
        int h = height[left] < height[right] ? height[left] : height[right];
        int w = right - left;
        int current_area = h * w;

        if (current_area > max_water) {
            max_water = current_area;
        }

        // Advance the pointer at the shorter boundary
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }

    return max_water;
}