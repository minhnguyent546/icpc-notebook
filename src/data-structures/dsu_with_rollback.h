/**
 * Description: a DSU with rollback operation, allow rollbacking to the previous snapshot.
 * Time: $O(\log{N})$ per operation and $O(k)$ for rollback where $k$ is the
 * distance between snapshot to restore and the current snapshot.
 */

struct DsuWithRollback {
    int n, comp;
    vector<int> par, rank;
    vector<tuple<int, int, int, int>> history;
    DsuWithRollback() {}
    DsuWithRollback(int _n): n(_n), comp(n), par(n), rank(n) {
        iota(par.begin(), par.end(), 0);
    }
    int find(int v) {
        while (v != par[v]) v = par[v];
        return v;
    }
    bool unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        --comp;
        if (rank[u] < rank[v]) swap(u, v);
        history.emplace_back(u, rank[u], v, rank[v]);
        par[v] = u;
        if (rank[u] == rank[v]) ++rank[u];
        return true;
    }
    int snapshot() { return history.size(); }
    void rollback(int until) {
        while (snapshot() > until) {
            auto [u, rank_u, v, rank_v] = history.back();
            history.pop_back();
            ++comp;
            par[u] = u, par[v] = v;
            rank[u] = rank_u, rank[v] = rank_v;
        }
    }
};
