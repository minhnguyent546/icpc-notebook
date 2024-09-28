/**
 * Description: building an auxiliary tree which contains vertices from the given
 * vertex set of size $N$ and their LCAs, there are at most $N - 1$ LCA vertices will be added,
 * so the auxiliary tree will have at most $2N - 1$ vertices.
 * Time: $O(N\log{N})$
 */

#include "./lca.h"

int build_tree(vector<vector<pair<int, int>>> &aux_g, vector<int> &vers, LCA &lca) {
    auto comp = [&](int u, int v) { return lca.pos[u] < lca.pos[v]; };
    sort(vers.begin(), vers.end(), comp);
    for (int i = 0, sz = (int) vers.size(); i < sz - 1; ++i) {
        vers.emplace_back(lca.lca(vers[i], vers[i + 1]));
    }
    sort(vers.begin(), vers.end(), comp);
    vers.erase(unique(vers.begin(), vers.end()), vers.end());
    int aux_root = vers[0];
    vector<int> stack = {aux_root};
    for (int i = 1; i < (int) vers.size(); ++i) {
        int u = vers[i];
        while (!stack.empty() && !lca.is_anc(stack.back(), u)) stack.pop_back();
        assert(!stack.empty());
        int w = lca.depth[u] - lca.depth[stack.back()];
        aux_g[stack.back()].push_back({u, w});
        stack.emplace_back(u);
    }
    return aux_root;
};
