#include "point.h"

vector<Point> CH_Andrew(vector<Point> &Pts) { // overall O(n log n)
    int n = Pts.size(), k = 0;
    vector<Point> H(2 * n);
    sort(Pts.begin(), Pts.end());
    for (int i = 0; i < n; ++i) {
        while ((k >= 2) && !ccw(H[k - 2], H[k - 1], Pts[i])) --k;
        H[k++] = Pts[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; --i) {
        while ((k >= t) && !ccw(H[k - 2], H[k - 1], Pts[i])) --k;
        H[k++] = Pts[i];
    }
    H.resize(k);
    return H;
}