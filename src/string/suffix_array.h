struct SuffixArray {
    string s;
    int n, lim;
    vector<int> sa, lcp, rank;
    SuffixArray(const string &_s, int _lim = 256) : s(_s), n(s.length() + 1), lim(_lim), sa(n), lcp(n), rank(n) {
        s += '$';
        build();
        kasai();
        sa.erase(sa.begin());
        lcp.erase(lcp.begin());
        s.pop_back();
    }
    void build() {
        vector<int> nrank(n), norder(n), cnt(max(n, lim));
        for (int i = 0; i < n; ++i) {
            sa[i] = i; rank[i] = s[i];
        }
        for (int k = 0, rank_cnt = 0; rank_cnt < n - 1; k = max(1, k * 2), lim = rank_cnt + 1) {
            // counting sort. 
            for (int i = 0; i < n; ++i) norder[i] = (sa[i] - k + n) % n;
            for (int i = 0; i < n; ++i) cnt[rank[i]]++;
            for (int i = 1; i < lim; ++i) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; --i) sa[--cnt[rank[norder[i]]]] = norder[i];
            rank[sa[0]] = rank_cnt = 0;
            for (int i = 1; i < n; ++i) {
                int u = sa[i], v = sa[i - 1];
                int nu = u + k, nv = v + k;
                if (nu >= n) nu -= n; 
                if (nv >= n) nv -= n;
                if (rank[u] != rank[v] || rank[nu] != rank[nv]) ++rank_cnt;
                nrank[sa[i]] = rank_cnt;
            }
            for (int i = 0; i < rank_cnt + 1; ++i) cnt[i] = 0;
            rank.swap(nrank);
        }
    }
    void kasai() {
        for (int i = 0; i < n; ++i) rank[sa[i]] = i;
        for (int i = 0, k = 0; i < n - 1; ++i, k = max(0, k - 1)) {
            int j = sa[rank[i] - 1];
            while (s[i + k] == s[j + k]) k++;
            lcp[rank[i]] = k;
        }
        // Note: lcp[i] = longest common prefix(sa[i - 1], sa[i]).
    }
};