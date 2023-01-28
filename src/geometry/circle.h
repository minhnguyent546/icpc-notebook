#include "point.h"

int insideCircle(const Point& p, const Point& center, ftype r) {
    ftype d = norm(p - center);
    ftype rSq = r * r;
    return fabs(d - rSq) < EPS ? 0 : (d - rSq >= EPS ? 1 : -1);
}
bool circle2PointsR(const Point& p1, const Point& p2, ftype r, Point& c) {
    double h = r * r - norm(p1 - p2) / 4.0;
    if (fabs(h) < 0) return false;
    h = sqrt(h);
    Point perp = (p2 - p1).rotate(PI / 2.0);
    Point m = (p1 + p2) / 2.0;
    c = m + perp * (h / abs(perp));
    return true;
}