/** Finding k smallest shortest path from vertex s to vertex t,
 *  each vertex can be visited more than once.
 */
using adj_list = vector<vector<pair<int, int>>>;
vector<int> k_smallest(const adj_list &g, int k, int s, int t) {
    int n = (int) g.size();
    vector<long long> ans;
    vector<int> cnt(n);
    using pli = pair<long long, int>;
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pq.emplace(0, s);
    while (!pq.empty() && cnt[t] < k) {
        int u = pq.top().second;
        long long d = pq.top().first; 
        pq.pop();
        if (cnt[u] == k) continue;
        cnt[u]++;
        if (u == t) {
            ans.push_back(d);
        }
        for (auto [v, cost] : g[u]) {
            pq.emplace(d + cost, v);
        }
    }
    assert(ans.size() == k);
    return ans;
}