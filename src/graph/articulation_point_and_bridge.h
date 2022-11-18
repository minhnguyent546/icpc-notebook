/**
 * Description: finding articulation points and bridges in a simple undirected graph. 
 * Tested: https://oj.vnoi.info/problem/graph_
 */
const int N = (int) 1e5;
vector<int> g[N];
int num[N], low[N], dfs_timer;
bool joint[N];
vector<pair<int, int>> bridges;
void dfs(int u, int prev) {
    low[u] = num[u] = ++dfs_timer;
    int child = 0;
    for (int v : g[u]) {
        if (v == prev) continue;
        if (num[v]) low[u] = min(low[u], num[v]);
        else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            child++;
            if (low[v] >= num[v]) {
                bridges.emplace_back(u, v);
            }
            if (u != prev && low[v] >= num[u]) joint[u] = true;
        }
    }
    if (u == prev && child > 1) joint[u] = true;    
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 0; i < n; ++i) {
        if (!num[i]) dfs(i, i);
    }
    return 0;
}