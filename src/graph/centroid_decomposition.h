/**
 * Description: centroid decomposition technique for solving various task in a
 * tree related to all paths/all pairs in tree.
 * Time: O(N log N)
 */

const int N = (int) 1e5;
vector <int > g[N];
int sz[N];
bool vis[N];
void dfs_sz (int u, int par = -1) {
    sz[u] = 1;
    for (int v : g[u]) {
        if (v == par || vis[v]) continue;
        dfs_sz (v, u);
        sz[u] += sz[v];
    }
}
int find_cend (int u, int s, int par = -1) {
    for (int v : g[u]) {
        if (v == par || vis[v]) { continue ; }
            if (sz[v] * 2 > s) { return find_cend (v, s, u); }
        }
    return u;
}
void solve (int u) {
    dfs_sz (u);
    int c = find_cend (u, sz[u]);
    vis[c] = true;
    // solve for vertex c...
    for (int v : g[c]) {
        if (vis[v]) continue;
        solve(v);
    }
}
