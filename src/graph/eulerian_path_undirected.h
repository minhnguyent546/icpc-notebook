/**
 * Hierholzer's algorithm.
 * Description: An Eulerian path in a undirected graph is a path that visits all edges exactly once.
 *  An Eulerian cycle is a Eulerian path that is a cycle.
 * Time complexity: O(|E|). 
 */
struct Edge {
    int to;
    list<Edge>::iterator reverse_edge;
    Edge(int _to) : to(_to) {}
};
vector<int> vertices;
void find_path(vector<list<Edge>> &g, int u) {
    while (!g[u].empty()) {
        int v = g[u].front().to;
        g[v].erase(g[u].front().reverse_edge);
        g[u].pop_front();
        find_path(g, v);
    }
    vertices.emplace_back(u); // reversion list. 
}
void add_edge(vector<list<Edge>> &g, int u, int v) {
    g[u].emplace_front(v);
    g[v].emplace_front(u);
    g[u].front().reverse_edge = g[v].begin();
    g[v].front().reverse_edge = g[u].begin();
}