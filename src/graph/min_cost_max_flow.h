const int N = (int) 1e3 + 3;
const int oo = (int) 1e9;
int trace[N], c[N][N], f[N][N], d[N];
vector<pair<int, int>> adj[N];
int n, s, t, ans;

bool FindPath(){
    for (int u = 1; u <= n; ++u) {
        trace[u] = -1;
        d[u] = oo;
    }

    trace[s] = s;
    d[s] = 0;

    using Node = pair<int, int>;
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({0, s});
    while (!pq.empty()){
        auto [l, u] = pq.top();
        pq.pop();

        if (l > d[u]) continue;
        for (auto [w, v] : adj[u]){
            if (c[u][v] > f[u][v]){
                if (l + (f[u][v] >= 0 ? w : -w) < d[v]){
                    d[v] = l + (f[u][v] >= 0 ? w : -w);
                    trace[v] = u;

                    pq.push({d[v], v});
                }
            }
        }
    }

    return trace[t] != -1;
}

void Enlarge(){
    int u, v = t, mn = oo;
    while (v != s){
        u = trace[v];
        mn = min(mn, c[u][v] - f[u][v]);
        v = u;
    }

    v = t;
    while(v != s){
        u = trace[v];
        f[u][v] += mn;
        f[v][u] -= mn;
        v = u;
    }

    ans += d[t] * mn;
}

int solve() {
    // Xu ly dau vao

    while (FindPath()){
        Enlarge();
    }

    cout << ans << '\n';
    return 0;
}
