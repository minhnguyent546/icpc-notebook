/**
 * Description: finds a way to assign values to boolean variables a, b, c,..
 *   of a 2-SAT problem (each clause has at most two variables) so that
 *   the following formula becomes true: (a | b) & (~a | c) & (b | ~c)...
 * Time complexity: O(V + E) where V is the number of boolean variables
 *   and E is the number of clauses.
 * Usage:
 *   TwoSat twosat(number of boolean variables);
 *   twosat.either(a, ~b); // a is true or b is false
 *   twosat.solve(); // return true iff the above formula is satisfiable
 */

struct TwoSat {
    int n;
    vector<vector<int>> g, tg; // g and transpose of g
    vector<int> comp, order;
    vector<bool> vis, vals;
    TwoSat(int _n): n(_n), g(2 * n), tg(2 * n),
        comp(2 * n), vis(2 * n), vals(n) {}
    void either(int u, int v) {
        u = max(2 * u, -2 * u - 1);
        v = max(2 * v, -2 * v - 1);
        g[u ^ 1].push_back(v);
        g[v ^ 1].push_back(u);
        tg[v].push_back(u ^ 1);
        tg[u].push_back(v ^ 1);
    }
    void set(int u) { either(u, u); }
    void dfs1(int u) {
        vis[u] = true;
        for (int v : g[u]) {
            if (!vis[v]) dfs1(v);
        }
        order.push_back(u);
    }
    void dfs2(int u, int scc_id) {
        comp[u] = scc_id;
        for (int v : tg[u]) {
            if (comp[v] == -1) dfs2(v, scc_id);
        }
    }
    bool solve() {
        for (int i = 0; i < 2 * n; ++i) {
            if (!vis[i]) dfs1(i);
        }
        fill(comp.begin(), comp.end(), -1);
        for (int i = 2 * n - 1, scc_id = 0; i >= 0; --i) {
            int u = order[i];
            if (comp[u] == -1) dfs2(u, scc_id++);
        }
        for (int i = 0; i < n; ++i) {
            int u = i * 2, nu = i * 2 + 1;
            if (comp[u] == comp[nu]) {
                return false;
            }
            vals[i] = comp[u] > comp[nu];
        }
        return true;
    }
    vector<bool> get_vals() { return vals; }
};