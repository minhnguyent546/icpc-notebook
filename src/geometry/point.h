const double PI = acos(-1);
const double EPS = 1e-9;
typedef double ftype;
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