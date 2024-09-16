/**
 * Description: Kuhn's algorithm for finding maximum matching in bipartite graph.
 * For faster algorithm, see Hopcroft-Karp algorithm.
 * $g$ should be a list of neighbors of the left partition, $mat[v]$ will be the match
 * for vertex $v$ on the right partition, or $-1$ if no matching edge contains $v$.
 * Usage: vector<int> mat(right\_sz, -1); bipartite\_matching(g, mat);
 * Time: $O(VE)$
 * Status: tested on:
 *   - https://open.kattis.com/problems/borders
 *   - https://open.kattis.com/problems/gopher2
 */

int bipartite_matching(vector<vector<int>> &g, vector<int> &mat) {
    int n_left = (int) g.size();
    int n_right = (int) mat.size();
    vector<bool> used(n_left), pre_used(n_left);
    // finding some arbitrary matching to improve performance
    for (int u = 0; u < n_left; ++u) {
        for (int v : g[u]) {
            if (mat[v] == -1) {
                mat[v] = u;
                pre_used[u] = true;
                break;
            }
        }
    }
    auto find_aug_path = [&](auto &&self, int u) -> bool {
        if (used[u]) return false;
        used[u] = true;
        for (int v : g[u]) {
            if (mat[v] == -1 || self(self, mat[v])) {
                mat[v] = u;
                return true;
            }
        }
        return false;
    };
    for (int u = 0; u < n_left; ++u) {
        if (pre_used[u]) continue;
        fill(used.begin(), used.end(), false);
        find_aug_path(find_aug_path, u);
    }
    return n_right - count(mat.begin(), mat.end(), -1);
}
