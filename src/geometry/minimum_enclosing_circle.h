/**
 * Description: computes the minimum circle that encloses all the given points.
 */

#include "point.h"
// TODO: make it compatible with circle.h

Point center_from(double bx, double by, double cx, double cy) {
    double B = bx * bx + by * by, C = cx * cx + cy * cy, D = bx * cy - by * cx;
    return Point((cy * B - by * C) / (2 * D), (bx * C - cx * B) / (2 * D));
}

Circle Circle_from(Point A, Point B, Point C) {
    Point I = center_from(B.x - A.x, B.y - A.y, C.x - A.x, C.y - A.y);
    return Circle(I + A, abs(I));
}

const int N = 100005;
int n, x[N], y[N];
Point a[N];

Circle emo_welzl(int n, vector<Point> T) {
    if (T.size() == 3 || n == 0) {
        if (T.size() == 0) return Circle(Point(0, 0), -1);
        if (T.size() == 1) return Circle(T[0], 0);
        if (T.size() == 2) return Circle((T[0] + T[1]) / 2, abs(T[0] - T[1]) / 2);
        return Circle_from(T[0], T[1], T[2]);
    }
    random_shuffle(a + 1, a + n + 1);
    Circle Result = emo_welzl(0, T);
    for (int i = 1; i <= n; i++)
        if (abs(Result.x - a[i]) > Result.y + 1e-9) {
            T.push_back(a[i]);
            Result = emo_welzl(i - 1, T);
            T.pop_back();
        }
    return Result;
}