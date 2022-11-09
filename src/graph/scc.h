/**
 * Description: Tarjan's algorithm finds strongly connected components
 *  in a directed graph. If vertices u and v belong to the same component, 
 *  then scc_id[u] == scc_id[v].
 * Tested: https://judge.yosupo.jp/problem/scc
 */
const int N = (int) 5e5;
vector<int> g[N], st;
int low[N], num[N], dfs_timer, scc_id[N], scc;
bool used[N];
void Tarjan(int u) {
    low[u] = num[u] = ++dfs_timer;
    st.push_back(u);
    for (int v : g[u]) {
        if (used[v]) continue;
        if (num[v] == 0) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else {
            low[u] = min(low[u], num[v]);
        }
    }
    if (low[u] == num[u]) {
        int v;
        do {
            v = st.back(); st.pop_back();
            debug(u, v)
            used[v] = true;
            scc_id[v] = scc;
        } while (v != u);
        scc++;
    }
}