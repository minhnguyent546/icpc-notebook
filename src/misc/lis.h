/**
 * Description: finding increasing subsequence of an array.
 * Time: $O(N\log{N})$
 * Status: tested on https://judge.yosupo.jp/problem/longest_increasing_subsequence
 */

int lis(const vector<int> &arr, vector<int> &indices) {
    int n = (int) arr.size();
    vector<int> dp, idx;
    vector<int> trace(n, -1);
    for (int i = 0; i < n; ++i) {
        // change to lower_bound to get a strictly increasing subsequence.
        int j = (int) (upper_bound(dp.begin(), dp.end(), arr[i]) - dp.begin());
        if (j == (int) dp.size()) {
            dp.emplace_back(arr[i]);
            trace[i] = (idx.empty() ? -1 : idx.back());
            idx.emplace_back(i);
        } else {
            dp[j] = arr[i];
            trace[i] = (j > 0 ? idx[j - 1] : -1);
            idx[j] = i;
        }
    }
    int cur = idx.back();
    while (cur != -1) {
        indices.emplace_back(cur);
        cur = trace[cur];
    }
    reverse(indices.begin(), indices.end());
    assert(indices.size() == dp.size());
    return dp.size();
}
