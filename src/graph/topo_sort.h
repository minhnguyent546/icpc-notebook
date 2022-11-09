/**
 * Description: A topological sort of a directed acyclic graph
 *  is a linear ordering of its vertices such that for every directed edge
 *  from vertex u to vertex v, u comes before v in the ordering.
 * Note: If there are cycles, the returned list will have size smaller than n (i.e, topo.size() < n). 
 * Tested: https://judge.yosupo.jp/problem/scc
 */
vector<int> topo_sort(const vector<vector<int>> &g) {
    int n = (int) g.size();
    vector<int> indeg(n);
    for (int u = 0; u < n; ++u) {
        for (int v : g[u]) indeg[v]++;
    }
    queue<int> q; // Note: use min-heap to get the smallest lexicographical order.
    for (int u = 0; u < n; ++u) {
        if (indeg[u] == 0) q.emplace(u);
    }
    vector<int> topo;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.emplace_back(u);
        for (int v : g[u]) {
            if (--indeg[v] == 0) q.emplace(v);
        }
    }
    return topo;
}