/**
 * Description: finding lowest common ancestor (LCA) between any two vertices.
 * Time: $<O(N\log{N}), O(1)>$.
 * Status: tested on https://judge.yosupo.jp/problem/lca
 */

#include "../data-structures/rmq.h"

struct LCA {
    int n;
    vector<int> pos, depth;
    vector<vector<int>> g;
    vector<pair<int, int>> tour;
    RMQ<pair<int, int>> rmq;
    LCA(int _n): n(_n), pos(n), depth(n), g(n) {}
    void add_edge(int u, int v) { g[u].emplace_back(v); }
    void build(int root = 0) {
        dfs(root);
        rmq.build(tour);
    }
    void dfs(int u, int par = -1) {
        pos[u] = (int) tour.size();
        tour.emplace_back(depth[u], u);
        for (int v : g[u]) {
            if (v == par) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
            tour.emplace_back(depth[u], u);
        }
    }
    int lca(int u, int v) {
        u = pos[u], v = pos[v];
        if (u > v) swap(u, v);
        return rmq.get(u, v).second;
    }
    int rooted_lca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
};
