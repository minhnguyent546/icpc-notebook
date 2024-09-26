/**
 * Description: finding the k-th smallest element in the array in linear time.
 * The array should be shuffled before calling this function.
 * Time: $O(N)$
 * Status: tested on https://www.codechef.com/problems/CD1IT1
 */

template<typename T>
T kth_order_statistic(vector<T> arr, int k) {
    int n = (int) arr.size();
    k -= 1;
    for (int l = 0, r = n - 1;;) {
        if (r <= l + 1) {
            if (r == l + 1 && arr[r] < arr[l]) {
                swap(arr[l], arr[r]);
            }
            return arr[k];
        }
        int mid = l + (r - l) / 2;
        swap(arr[mid], arr[l + 1]);
        if (arr[l] > arr[r]) swap(arr[l], arr[r]);
        if (arr[l + 1] > arr[r]) swap(arr[l + 1], arr[r]);
        if (arr[l] > arr[l + 1]) swap(arr[l], arr[l + 1]);

        // performing division
        // barrier is arr[l + 1], i.e. median among a[l], a[l + 1], a[r]
        int i = l + 1, j = r;
        T pivot = arr[l + 1];
        for (;;) {
            while (arr[++i] < pivot);
            while (arr[--j] > pivot);
            if (i > j) break;
            swap(arr[i], arr[j]);
        }

        // inserting the barrier
        arr[l + 1] = arr[j];
        arr[j] = pivot;

        if (j >= k) r = j - 1;
        if (j <= k) l = i;
    }
}
