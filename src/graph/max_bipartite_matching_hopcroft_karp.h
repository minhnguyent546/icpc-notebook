/**
 * Description: Hopcroft–Karp algorithm is a fast algorithm for finding
 * maximum matching in bipartite graph.
 * $g$ should be a list of neighbors of the left partition.
 * Usage:
 *   - vector<int> left\_mat(n\_left, -1), right\_mat(n\_right, -1);
 *   - hopcroft\_karp(g, left\_mat, right\_mat);
 * Time: $O(E\sqrt{V})$
 * Status: tested on https://judge.yosupo.jp/problem/bipartitematching
 */

int hopcroft_karp(vector<vector<int>> &g, vector<int> &left_mat, vector<int> &right_mat) {
    int n_left = (int) g.size();
    vector<int> dist(n_left);
    int matching = 0;

    auto bfs = [&]() {
        queue<int> que;
        for (int i = 0; i < (int) left_mat.size(); ++i) {
            if (left_mat[i] == -1) {
                dist[i] = 0;
                que.emplace(i);
            } else {
                dist[i] = -1;
            }
        }
        while (!que.empty()) {
            int u = que.front(); que.pop();
            for (int v : g[u]) {
                if (right_mat[v] != -1 && dist[right_mat[v]] == -1) {
                    dist[right_mat[v]] = dist[u] + 1;
                    que.emplace(right_mat[v]);
                }
            }
        }
    };

    auto dfs = [&](auto &&self, int u) {
        for (int v : g[u]) {
            if (right_mat[v] == -1) {
                left_mat[u] = v;
                right_mat[v] = u;
                return true;
            }
        }
        for (int v : g[u]) {
            if (dist[right_mat[v]] == dist[u] + 1) {
                if (self(self, right_mat[v])) {
                    left_mat[u] = v, right_mat[v] = u;
                    return true;
                }
            }
        }
        dist[u] = -1;
        return false;
    };

    while (true) {
        bfs();
        int augment = 0;
        for (int u = 0; u < n_left; ++u) {
            if (left_mat[u] == -1) {
                augment += dfs(dfs, u);
            }
        }
        if (!augment) break;
        matching += augment;
    }
    return matching;
}
