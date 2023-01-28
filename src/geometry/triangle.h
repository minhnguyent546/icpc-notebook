#include "point.h"
#include "line.h"

double areaTriangle(double ab, double bc, double ca) {
    double p = (ab + bc + ca) / 2;
    return sqrt(p) * sqrt(p - ab) * sqrt(p - bc) * sqrt(p - ca);
}
double rInCircle(double ab, double bc, double ca) {
    double p = (ab + bc + ca) / 2;
    return areaTriangle(ab, bc, ca) / p;
}
double rInCircle(Point a, Point b, Point c) {
    return rInCircle(abs(a - b), abs(b - c), abs(c - a));
}
bool inCircle(Point p1, Point p2, Point p3, Point &ctr, double &r) {
    r = rInCircle(p1, p2, p3);
    if (fabs(r) < EPS) return false;
    Line l1, l2;
    double ratio = abs(p2 - p1) / abs(p3 - p1);
    Point p = p2 + (p3 - p2) * (ratio / (1 + ratio));
    PointsToLine(p1, p, l1);
    ratio = abs(p1 - p2) / abs(p2 - p3);
    p = p1 + (p3 - p1) * ( ratio / (1 + ratio));
    PointsToLine(p2, p, l2);
    areIntersect(l1, l2, ctr);
    return true;
}
double rCircumCircle(double ab, double bc, double ca) {
    return ab * bc * ca / (4.0 * areaTriangle(ab, bc, ca));
}
double rCircumCircle(Point a, Point b, Point c) {
    return rCircumCircle(abs(b - a), abs(c - b), abs(a - c));
}