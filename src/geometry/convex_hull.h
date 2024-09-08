/**
 * Description: Andrew's algorithm for computing convex hull of a set of points.
 * Time: $O(n\log{n})$
 */

#include "point.h"

vector<Point> convex_hull(vector<Point> &&points) {
    int n = (int) points.size(), k = 0;
    if (n <= 2) return points;
    vector<Point> ch(n * 2);
    sort(points.begin(), points.end());
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && sign(cross(ch[k - 1] - ch[k - 2], points[i] - ch[k - 1])) <= -1) --k;
        ch[k++] = points[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; --i) {
        while (k >= t && sign(cross(ch[k - 1] - ch[k - 2], points[i] - ch[k - 1])) <= -1) --k;
        ch[k++] = points[i];
    }
    ch.resize(k - 1);
    return ch;
}
