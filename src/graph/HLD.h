const int INF = 0x3f3f3f3f;
template<class SegmentTree>
struct HLD { // vertex update and max query on path u -> v
    int n;
    vector<vector<int>> g;
    SegmentTree seg_tree;
    vector<int> par, top, depth, sz, id;
    int timer = 0;
    bool VAL_IN_EDGE = false;
    HLD() {}
    HLD(int _n): n(_n), g(n), seg_tree(n), par(n), top(n), depth(n), sz(n), id(n) {}
    void build(int root = 0) {
        dfs_sz(root);
        dfs_hld(root);
    }
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void dfs_sz(int u) {
        sz[u] = 1;
        for (int &v : g[u]) { // MUST BE ref for the swap below
            par[v] = u;
            depth[v] = depth[u] + 1;
            g[v].erase(find(g[v].begin(), g[v].end(), u));
            dfs_sz(v);
            sz[u] += sz[v];
            if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
        }
    }
    void dfs_hld(int u) {
        id[u] = timer++;
        for (int v : g[u]) {
            top[v] = (v == g[u][0] ? top[u] : v);
            dfs_hld(v);
        }
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (depth[top[u]] > depth[top[v]]) swap(u, v);
            v = par[top[v]];
        }
        // now u, v is in the same heavy-chain
        return (depth[u] < depth[v] ? u : v);
    }
    int rooted_lca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
    void set_vertex(int v, int x) {
        seg_tree.set(id[v], x);
    }
    void set_edge(int u, int v, int x) {
        if (u != par[v]) swap(u, v);
        seg_tree.set(id[v], x);
    }
    void set_subtree(int v, int x) {
        // modify segment_tree so that it supports range update
        seg_tree.set_range(id[v] + VAL_IN_EDGE, id[v] + sz[v] - 1, x);
    }
    int query_path(int u, int v) {
        int res = -INF;
        while (top[u] != top[v]) {
            if (depth[top[u]] > depth[top[v]]) swap(u, v);
            int cur = seg_tree.query(id[top[v]], id[v]);
            res = max(res, cur);
            v = par[top[v]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        int cur = seg_tree.query(id[u] + VAL_IN_EDGE, id[v]);
        res = max(res, cur);
        return res;
    }
};
