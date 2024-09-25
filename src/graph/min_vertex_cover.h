/**
 * Description: finding minimum vertex cover in a bipartite graph. The minimum
 * vertex cover set and the maximum matching set have the same size.
 * The complement of a vertex cover in any graph is an independent set.
 */

#include "./max_bipartite_matching_kuhn.h"

vector<int> min_vertex_cover(vector<vector<int>> &g, int n_left, int n_right) {
    vector<int> mat(n_right, -1), cover;
    int max_matching = bipartite_matching(g, mat);
    vector<bool> in_cover(n_left), visited(n_right);
    for (int u : mat) {
        if (u != -1) in_cover[u] = true;
    }
    queue<int> que;
    for (int u = 0; u < n_left; ++u) {
        if (!in_cover[u]) que.emplace(u);
    }
    while (!que.empty()) {
        int u = que.front(); que.pop();
        in_cover[u] = false;
        for (int v : g[u]) {
            if (!visited[v] && mat[v] != -1) {
                visited[v] = true;
                que.emplace(mat[v]);
            }
        }
    }
    for (int i = 0; i < n_left; ++i) {
        if (in_cover[i]) cover.emplace_back(i);
    }
    for (int i = 0; i < n_right; ++i) {
        if (visited[i]) cover.emplace_back(i + n_left);
    }
    assert((int) cover.size() == max_matching);
    return cover;
}
