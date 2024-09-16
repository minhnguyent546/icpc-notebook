/**
 * Description: Kuhn's algorithm for finding maximum matching in bipartite graph.
 * $g$ should be a list of neighbors of the left partition, $mat[v]$ will be the match
 * for vertex $v$ on the right partition, or $-1$ if no matching edge contains $v$.
 * Usage: vector<int> mat(right\_sz, -1); bipartite\_matching(g, mat);
 * Time: $O(VE)$
 */

using vi = vector<int>;
bool find_aug_path(int u, vector<vi> &g, vi &mat, vector<bool> &used) {
    if (used[u]) return false;
    used[u] = true;
    for (int v : g[u]) {
        if (mat[v] == -1 || find_aug_path(mat[v], g, mat, used)) {
            mat[v] = u;
            return true;
        }
    }
    return false;
}

int bipartite_matching(vector<vi> &g, vi &mat) {
    int left_sz = (int) g.size();
    int right_sz = (int) mat.size();
    vector<bool> used(left_sz), pre_used(left_sz);
    // finding some arbitrary matching to improve performance
    for (int u = 0; u < left_sz; ++u) {
        for (int v : g[u]) {
            if (mat[v] == -1) {
                mat[v] = u;
                pre_used[u] = true;
                break;
            }
        }
    }
    for (int u = 0; u < left_sz; ++u) {
        if (pre_used[u]) continue;
        fill(used.begin(), used.end(), false);
        find_aug_path(u, g, mat, used);
    }

    return right_sz - count(mat.begin(), mat.end(), -1);
}
