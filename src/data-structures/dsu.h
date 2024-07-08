struct Dsu {
    int n;
    vector<int> par, sz;
    Dsu(int _n) : n(_n) {
        sz.resize(n, 1);
        par.resize(n);
        iota(par.begin(), par.end(), 0);
    }
    int find(int v) {
        // finding leader/parrent of set that contains the element v.
        // with {path compression optimization}.
        return (v == par[v] ? v : par[v] = find(par[v]));
    }
    bool same(int u, int v) {
        return find(u) == find(v);
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
            result[id[leader[i]]].push_back(i);
        }
        return result;
    }
};