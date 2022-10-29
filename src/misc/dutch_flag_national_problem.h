void dutch_flag_national(vector<int> &arr) {
    // All elements that are LESS than pivot are moved to the LEFT.
    // All elements that are GREATER than pivot are moved to the RIGHT.
    // E.g. [1, 2, 0, 0, 2, 2, 1], pivot = 1 -> [0, 0, 1, 1, 2, 2, 2].
    int n = (int) arr.size();
    int i = 0, j = 0, k = n - 1;
    int pivot = 1;
    // 0....i....j....k....n
    while (j <= k) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
            j++;
        }
        else if (arr[j] > pivot) {
            swap(arr[j], arr[k]);
            k--;
        }
        else {
            j++;
        }
    }
    // 0 <= index <= i - 1: arr[index] < mid.
    // i <= index <= k: arr[index] = mid.
    // k + 1 <= index < sz: arr[index] > mid.
} 