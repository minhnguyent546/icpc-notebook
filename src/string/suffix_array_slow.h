vector<int> suffix_array_slow(string &s) {
    s += '$';
    int n = (int) s.size();
    vector<int> order(n), rank(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i; rank[i] = s[i];
    }
    for (int k = 0; k < n; k = max(1, k * 2)) {
        stable_sort(sa.begin(), sa.end(), [&](int i, int j) {
            return make_pair(rank[i], rank[(i + k) % n]) < make_pair(rank[j], rank[(j + k) % n]);
        });
        vector<int> nrank(n);
        for (int i = 0, cnt = 0; i < n; ++i) {
            if (i > 0 && rank[order[i]] != rank[order[i - 1]]) ++cnt;
            else if (i > 0 && rank[(order[i] + k) % n] != rank[(order[i - 1] + k) % n]) ++cnt;
            nrank[order[i]] = cnt;
        }
        rank.swap(nrank);
    }
    s.pop_back(); order.erase(order.begin());
    return order;
    // Time complexity: O(N * log(N)^2). 
}