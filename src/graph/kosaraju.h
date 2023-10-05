/**
 * Description: Kosaraju's algorithm finds strongly connected components (SCC)
 *   in a directed graph in a straightforward way. Two vertices u and v
 *   belong to the same component iff scc_id[u] == scc_id[v]. This algorithm
 *   generates connected components numbered in topological order in
 *   corresponding condensation graph.
 */
const int N = (int) 1e5;
vector<int> g[N], rev_g[N], vers;
int scc_id[N];
bool vis[N];
int n, m;

void dfs1(int u) {
    vis[u] = true;
    for (int v : g[u]) {
        if (!vis[v]) {
            dfs1(v);
        }
    }
    vers.push_back(u);
}
void dfs2(int u, int id) {
    scc_id[u] = id;
    vis[u] = true;
    for (int v : rev_g[u]) {
        if (!vis[v]) {
            dfs2(v, id);
        }
    }
}
void Kosaraju() {
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) dfs1(i);
    }
    memset(vis, 0, sizeof vis);
    int scc_cnt = 0;
    // iterating in reverse order
    for (int i = n - 1; i >= 0; --i) {
        int u = vers[i];
        if (!vis[u]) {
            dfs2(u, ++scc_cnt);
        }
    }
    cout << scc_cnt << '\n';
    for (int i = 0; i < n; ++i) {
        cout << scc_id[i] << " \n"[i == n - 1];
    }
}