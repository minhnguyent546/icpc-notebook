/**
 * Description: given $N$ points in the plane, the distance between two points
 * is calculated as Manhattan distance. The function returns the list of edges
 * which are guaranteed to contain a MST in the format (weight, u, v)
 * of size up to $4N$
 * Time: $O(N\log{N})$.
 * Status: tested on https://judge.yosupo.jp/problem/manhattanmst, https://open.kattis.com/problems/gridmst
 */

struct Point {
    int64_t x, y;
};
vector<tuple<int64_t, int, int>> manhattan_mst(vector<Point> ps) {
    vector<int> indices(ps.size());
    iota(indices.begin(), indices.end(), 0);
    vector<tuple<int64_t, int, int>> edges;
    for (int rot = 0; rot < 4; ++rot) {
        sort(indices.begin(), indices.end(), [&](int i, int j) {
            return (ps[i].x + ps[i].y < ps[j].x + ps[j].y);
        });
        map<int, int, greater<int>> active; // (xd, id)
        for (int i : indices) {
            for (auto it = active.lower_bound(ps[i].x);
                 it != active.end(); active.erase(it++)) {
                int j = it->second;
                if (ps[i].x - ps[i].y > ps[j].x - ps[j].y) break;
                assert(ps[i].x >= ps[j].x && ps[i].y >= ps[j].y);
                edges.emplace_back(ps[i].x - ps[j].x + ps[i].y - ps[j].y, i, j);
            }
            active[ps[i].x] = i;
        }
        for (Point &p : ps) {
            if (rot & 1) p.x *= -1;
            else swap(p.x, p.y);
        }
    }
    return edges;
}
