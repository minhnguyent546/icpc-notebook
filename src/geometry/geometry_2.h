const double PI = acos(-1);
const double EPS = 1e-9;
typedef double ftype;
/*---------------POINT------------------*/
struct point {
    ftype x, y;
    point(ftype _x = 0, ftype _y = 0): x(_x), y(_y) {}
    point& operator+=(const point& other) {
        x += other.x; y += other.y; return *this;
    }
    point& operator-=(const point& other) {
        x -= other.x; y -= other.y; return *this;
    }
    point& operator*=(ftype t) {
        x *= t; y *= t; return *this;
    }
    point& operator/=(ftype t) {
        x /= t; y /= t; return *this;
    }
    point operator+(const point& other) const {
        return point(*this) += other;
    }
    point operator-(const point& other) const {
        return point(*this) -= other;
    }
    point operator*(ftype t) const {
        return point(*this) *= t;
    }
    point operator/(ftype t) const {
        return point(*this) /= t;
    }
    point rotate(double angle) const {
        return point(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
    }
    friend istream& operator>>(istream &in, point &t);
    friend ostream& operator<<(ostream &out, const point& t);
    bool operator<(const point& other) const {
        if (fabs(x - other.x) < EPS)
            return y < other.y;
        return x < other.x;
    }
};

istream& operator>>(istream &in, point &t) {
    in >> t.x >> t.y;
    return in;
}
ostream& operator<<(ostream &out, const point& t) {
    out << t.x << ' ' << t.y;
    return out;
}

ftype dot(point a, point b) {return a.x * b.x + a.y * b.y;}
ftype norm(point a) {return dot(a, a);}
ftype abs(point a) {return sqrt(norm(a));}
ftype angle(point a, point b) {return acos(dot(a, b) / (abs(a) * abs(b)));}
ftype proj(point a, point b) {return dot(a, b) / abs(b);}
ftype cross(point a, point b) {return a.x * b.y - a.y * b.x;}
bool ccw(point a, point b, point c) {return cross(b - a, c - a) > EPS;}
bool collinear(point a, point b, point c) {return fabs(cross(b - a, c - a)) < EPS;}
point intersect(point a1, point d1, point a2, point d2) {
    double t = cross(a2 - a1, d2) / cross(d1, d2);
    return a1 + d1 * t;
}


/*---------------LINE------------------*/

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
/*---------------Circle------------------*/
int insideCircle(const point& p, const point& center, ftype r) {
    ftype d = norm(p - center);
    ftype rSq = r * r;
    return fabs(d - rSq) < EPS ? 0 : (d - rSq >= EPS ? 1 : -1);
}
bool circle2PointsR(const point& p1, const point& p2, ftype r, point& c) {
    double h = r * r - norm(p1 - p2) / 4.0;
    if (fabs(h) < 0) return false;
    h = sqrt(h);
    point perp = (p2 - p1).rotate(PI / 2.0);
    point m = (p1 + p2) / 2.0;
    c = m + perp * (h / abs(perp));
    return true;
}
/*---------------Triangle------------------*/
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
/*---------------Polygon------------------*/
double perimeter(const vector<point> &P) {
    double ans = 0.0;
    for (int i = 0; i < (int)P.size() - 1; ++i)
        ans += abs(P[i] - P[i + 1]);
    return ans;
}
double area(const vector<point> &P) {
    double ans = 0.0;
    for (int i = 0; i < (int)P.size() - 1; ++i)
        ans += (P[i].x * P[i + 1].y - P[i + 1].x * P[i].y);
    return fabs(ans) / 2.0;
}
bool isConvex(const vector<point> &P) {
    int n = (int)P.size();
    if (n <= 3) return false;
    bool firstTurn = ccw(P[0], P[1], P[2]);
    for (int i = 1; i < n - 1; ++i)
        if (ccw(P[i], P[i + 1], P[(i + 2) == n ? 1 : i + 2]) != firstTurn)
            return false;
    return true;
}
int insidePolygon(point pt, const vector<point> &P) {
    int n = (int)P.size();
    if (n <= 3) return -1;
    bool on_polygon = false;
    for (int i = 0; i < n - 1; ++i)
        if (fabs(abs(P[i] - pt) + abs(pt - P[i + 1]) - abs(P[i] - P[i + 1])) < EPS)
            on_polygon = true;
    if (on_polygon) return 0;
    double sum = 0.0;
    for (int i = 0; i < n - 1; ++i) {
        if (ccw(pt, P[i], P[i + 1]))
            sum += angle(P[i] - pt, P[i + 1] - pt);
        else
            sum -= angle(P[i] - pt, P[i + 1] - pt);
    }
    return fabs(sum) > PI ? 1 : -1;
}
/*---------------Convex Hull------------------*/
vector<point> CH_Andrew(vector<point> &Pts) { // overall O(n log n)
    int n = Pts.size(), k = 0;
    vector<point> H(2 * n);
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