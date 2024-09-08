struct Dsu {
    int n;
    vector<int> par, sz;
    Dsu(int _n) : n(_n), par(n), sz(n) { init(); }
    void init() {
        for (int i = 0; i < n; ++i) {
            par[i] = i, sz[i] = 1;
        }
    }
    int find(int v) {
        // finding leader/parrent of set that contains the element v.
        // with {path compression optimization}.
        while (v != par[v]) {
            v = par[v] = par[par[v]];
        }
        return v;
    }
    bool unite(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        par[v] = u;
        sz[u] += sz[v];
        return true;
    }
    vector<vector<int>> groups() {
        // returns the list of the "list of the vertices in a connected component".
        vector<int> leader(n);
        for (int i = 0; i < n; ++i) {
            leader[i] = find(i);
        }
        vector<int> id(n, -1);
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (id[leader[i]] == -1) {
                id[leader[i]] = count++;
            }
        }
        vector<vector<int>> result(count);
        for (int i = 0; i < n; ++i) {
            result[id[leader[i]]].emplace_back(i);
        }
        return result;
    }
};
