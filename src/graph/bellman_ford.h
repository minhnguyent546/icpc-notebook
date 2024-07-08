/**
 * Description: single source shortest path in a weighted (negative or positive) directed graph. 
 * Time: $O(VE)$.
 * Tested: https://open.kattis.com/problems/shortestpath3
 */

const int64_t INF = (int64_t) 2e18;
struct Edge {
    int u, v; // u -> v
    int64_t w;
    Edge() {}
    Edge(int _u, int _v, int64_t _w) : u(_u), v(_v), w(_w) {}
};
int n;
vector<Edge> edges;
vector<int64_t> bellmanFord(int s) {
    // dist[stating] = 0.
    // dist[u] = +INF, if u is unreachable. 
    // dist[u] = -INF, if there is a negative cycle on the path from s to u. 
    // -INF < dist[u] < +INF, otherwise.
    vector<int64_t> dist(n, INF);
    dist[s] = 0;
    for (int i = 0; i < n - 1; ++i) {
        bool any = false;
        for (auto [u, v, w] : edges) {
            if (dist[u] != INF && dist[v] > w + dist[u]) { 
                dist[v] = w + dist[u];
                any = true;
            }
        }
        if (!any) break;
    }
    // handle negative cycles
    for (int i = 0; i < n - 1; ++i) {
        for (auto [u, v, w] : edges) {
            if (dist[u] != INF && dist[v] > w + dist[u]) {
                dist[v] = -INF;
            }
        }
    }
    return dist;
}