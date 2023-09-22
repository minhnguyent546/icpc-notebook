/**
 * Description: an easier way to implement suffix array but run slower
 * Time: O(N * logN^2)
 */
struct SuffixArraySlow {
    string s;
    int n;
    vector<int> sa, lcp, rank;
    SuffixArraySlow(const string &_s): s(_s), n((int) s.size() + 1), sa(n), lcp(n), rank(n) {
        s += '$';
        build(); kasai();
        sa.erase(sa.begin()); lcp.erase(lcp.begin());
        rank.pop_back(); s.pop_back();
    }
    bool comp(int i, int j, int k) {
        return make_pair(rank[i], rank[(i + k) % n]) < make_pair(rank[j], rank[(j + k) % n]);
    }
    void build() {
        vector<int> nrank(n);
        for (int i = 0; i < n; ++i) {
            sa[i] = i; rank[i] = s[i];
        }
        for (int k = 0; k < n; k = max(1, k * 2)) {
            stable_sort(sa.begin(), sa.end(), [&](int i, int j) {
                return comp(i, j, k);
            });
            for (int i = 0, cnt = 0; i < n; ++i) {
                if (i > 0 && comp(sa[i - 1], sa[i], k)) ++cnt;
                nrank[sa[i]] = cnt;
            }
            rank.swap(nrank);
        }
    }
    void kasai() {
        for (int i = 0, k = 0; i < n - 1; ++i, k = max(0, k - 1)) {
            int j = sa[rank[i] - 1];
            while (s[i + k] == s[j + k]) ++k;
            lcp[rank[i]] = k;
        }
    }
};