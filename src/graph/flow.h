const int N = (int) 1e3 + 3;
const int oo = (int) 1e9;
int trace[N], c[N][N], f[N][N];
vector <int> adj[N];
int n, s, t;
bool FindPath() {
    for (int u = 1; u <= n; ++u) { trace[u] = 0; }
    queue <int > q;
    q.push(s);
    trace[s] = s;
    while (!q.empty ()) {
        int u = q.front ();
        q.pop ();
        for (int v : adj[u]) {
            if (! trace[v] && c[u][v] > f[u][v]) {
                trace[v] = u;
            if (v == t) { return 1; }
                q.push(v);
            }
        }
    }
    return 0;
}
void Enlarge () {
    int u, v = t, mn = oo;
    while (v != s) {
        u = trace[v];
        mn = min(mn , f[u][v] >= 0 ? c[u][v] - f[u][v] : -f[u][v]);
        v = u;
    }
    v = t;
    while (v != s) {
        u = trace[v];
        f[u][v] += mn;
        f[v][u] -= mn;
        v = u;
    }
}
int solve () {
    // Xu ly dau vao
    while (FindPath()) { Enlarge (); }
    int ans = 0;
    for (int u = 1; u <= n; ++u) { ans += f[u][t]; }
    cout << ans << '\n';
    return 0;
}
