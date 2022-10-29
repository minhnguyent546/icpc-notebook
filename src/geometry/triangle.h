double areaTriangle(double ab, double bc, double ca) {
    double p = (ab + bc + ca) / 2;
    return sqrt(p) * sqrt(p - ab) * sqrt(p - bc) * sqrt(p - ca);
}
double rInCircle(double ab, double bc, double ca) {
    double p = (ab + bc + ca) / 2;
    return areaTriangle(ab, bc, ca) / p;
}
double rInCircle(point a, point b, point c) {
    return rInCircle(abs(a - b), abs(b - c), abs(c - a));
}
bool inCircle(point p1, point p2, point p3, point &ctr, double &r) {
    r = rInCircle(p1, p2, p3);
    if (fabs(r) < EPS) return false;
    line l1, l2;
    double ratio = abs(p2 - p1) / abs(p3 - p1);
    point p = p2 + (p3 - p2) * (ratio / (1 + ratio));
    pointsToLine(p1, p, l1);
    ratio = abs(p1 - p2) / abs(p2 - p3);
    p = p1 + (p3 - p1) * ( ratio / (1 + ratio));
    pointsToLine(p2, p, l2);
    areIntersect(l1, l2, ctr);
    return true;
}
double rCircumCircle(double ab, double bc, double ca) {
    return ab * bc * ca / (4.0 * areaTriangle(ab, bc, ca));
}
double rCircumCircle(point a, point b, point c) {
    return rCircumCircle(abs(b - a), abs(c - b), abs(a - c));
}