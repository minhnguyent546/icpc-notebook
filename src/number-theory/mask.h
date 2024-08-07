int n;
void mask_example() {
    for (int mask = 0; mask < (1 << n); ++mask) {
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                // do something...
            }
        }
        // Time complexity: O(n * 2^n).
    }
    for (int mask = 0; mask < (1 << n); ++mask) {
        for (int submask = mask; ; submask = (submask - 1) & mask) {
            // do something...
            if (submask == 0) break;
        }
        // Time complexity: O(3^n).
    }
}