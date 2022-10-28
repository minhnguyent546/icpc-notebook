/**
 * Hierholzer's algorithm.
 * Description: An Eulerian path in a directed graph is a path that visits all edges exactly once.
 *  An Eulerian cycle is a Eulerian path that is a cycle.
 * Time complexity: O(|E|). 
 */
 vector<int> find_path_directed(const vector<vector<int>> &g, int s) {
    int n = (int) g.size();
    vector<int> stack, cur_edge(n), vertices;
    stack.push_back(s);
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        while (cur_edge[u] < (int) g[u].size()) {
            stack.push_back(u);
            u = g[u][cur_edge[u]++];
        }
        vertices.push_back(u);
    }
    reverse(vertices.begin(), vertices.end());
    return vertices;
}