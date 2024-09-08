const int N = (int) 1e3 + 3;
int64_t capacity[N][N], ans;
int trace[N];
vector<int> adj[N];
bool FindWays(int s, int t, int n){
    for (int u = 1; u <= n; ++u) {
        trace[u] = 0;
    }
    trace[s] = s;
    queue<int> q;
    q.push(s);
    while (!q.empty()){
        int u = q.front();
        q.pop();
        for (auto v: adj[u]){
            if (trace[v] == 0 && capacity[u][v] > 0){
                trace[v] = u;
                q.push(v);
            }
        }
    }
    return trace[t];
}
void Update(int s, int t){
    int u, v = t;
    int64_t mn = (int64_t) 1e18 + 7;
    while (v != s){
        u = trace[v];
        mn = min(mn, capacity[u][v]);
        v = u;
    }
    v = t;
    while (v != s){
        u = trace[v];
        capacity[u][v] -= mn;
        capacity[v][u] += mn;
        v = u;
    }
    ans += mn;
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        capacity[u][v] += w;
        adj[u].emplace_back(v), adj[v].emplace_back(u);
    }
    int s = 1, t = n;
    while (FindWays(s, t, n)){
        Update(s, t);
    }
    cout << ans << endl;
}
