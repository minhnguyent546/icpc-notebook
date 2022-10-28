struct line {
    double a, b, c;
    line (double _a = 0, double _b = 0, double _c = 0): a(_a), b(_b), c(_c) {}
    friend ostream & operator<<(ostream& out, const line& l);
};
ostream & operator<<(ostream& out, const line& l) {
    out << l.a << ' ' << l.b << ' ' << l.c;
    return out;
}
void pointsToLine(const point& p1, const point& p2, line& l) {
    if (fabs(p1.x - p2.x) < EPS)
        l = {1.0, 0.0, -p1.x};
    else {
        l.a = - (double)(p1.y - p2.y) / (p1.x - p2.x);
        l.b = 1.0;
        l.c =  - l.a * p1.x - l.b * p1.y;
    }
}
void pointsSlopeToLine(const point& p, double m, line& l) {
    l.a = -m;
    l.b = 1;
    l.c = -l.a * p.x - l.b * p.y;
}
bool areParallel(const line& l1, const line& l2) {
    return fabs(l1.a - l2.a) < EPS && fabs(l1.b - l2.b) < EPS;
}
bool areSame(const line& l1, const line& l2) {
    return areParallel(l1, l2) && fabs(l1.c - l2.c) < EPS;
}
bool areIntersect(line l1, line l2, point& p) {
    if (areParallel(l1, l2)) return false;
    p.x = - (l1.c * l2.b - l1.b * l2.c) / (l1.a * l2.b - l1.b * l2.a);
    if (fabs(l1.b) > EPS) p.y = - (l1.c + l1.a * p.x);
    else p.y = - (l2.c + l2.a * p.x);
    return 1;
}
double distToLine(point p, point a, point b, point& c) {
    double t = dot(p - a, b - a) / norm(b - a);
    c = a + (b - a) * t;
    return abs(c - p);
}
double distToSegment(point p, point a, point b, point& c) {
    double t = dot(p - a, b - a) / norm(b - a);
    if (t > 1.0)
        c = point(b.x, b.y);
    else if (t < 0.0)
        c = point(a.x, a.y);
    else
        c = a + (b - a) * t;
    return abs(c - p);
}
bool intersectTwoSegment(point a, point b, point c, point d) {
    ftype ABxAC = cross(b - a, c - a);
    ftype ABxAD = cross(b - a, d - a);
    ftype CDxCA = cross(d - c, a - c);
    ftype CDxCB = cross(d - c, b - c);
    if (ABxAC == 0 || ABxAD == 0 || CDxCA == 0 || CDxCB == 0) {
        if (ABxAC == 0 && dot(a - c, b - c) <= 0) return true;
        if (ABxAD == 0 && dot(a - d, b - d) <= 0) return true;
        if (CDxCA == 0 && dot(c - a, d - a) <= 0) return true;
        if (CDxCB == 0 && dot(c - b, d - b) <= 0) return true;
        return false;
    }
    return (ABxAC * ABxAD < 0 && CDxCA * CDxCB < 0);
}
void perpendicular(line l1, point p, line& l2) {
    if (fabs(l1.a) < EPS)
        l2 = {1.0, 0.0, -p.x};
    else {
        l2.a = -l1.b / l1.a;
        l2.b = 1.0;
        l2.c = -l2.a * p.x - l2.b * p.y;
    }
}