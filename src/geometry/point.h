#pragma once

const double PI = acos(-1);
const double EPS = 1e-9;
typedef double ftype;
struct Point {
    ftype x, y;
    Point(ftype _x = 0, ftype _y = 0): x(_x), y(_y) {}
    Point& operator+=(const Point& other) {
        x += other.x; y += other.y; return *this;
    }
    Point& operator-=(const Point& other) {
        x -= other.x; y -= other.y; return *this;
    }
    Point& operator*=(ftype t) {
        x *= t; y *= t; return *this;
    }
    Point& operator/=(ftype t) {
        x /= t; y /= t; return *this;
    }
    Point operator+(const Point& other) const {
        return Point(*this) += other;
    }
    Point operator-(const Point& other) const {
        return Point(*this) -= other;
    }
    Point operator*(ftype t) const {
        return Point(*this) *= t;
    }
    Point operator/(ftype t) const {
        return Point(*this) /= t;
    }
    Point rotate(double angle) const {
        return Point(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
    }
    friend istream& operator>>(istream &in, Point &t);
    friend ostream& operator<<(ostream &out, const Point& t);
    bool operator<(const Point& other) const {
        if (fabs(x - other.x) < EPS)
            return y < other.y;
        return x < other.x;
    }
};

istream& operator>>(istream &in, Point &t) {
    in >> t.x >> t.y;
    return in;
}
ostream& operator<<(ostream &out, const Point& t) {
    out << t.x << ' ' << t.y;
    return out;
}

ftype dot(Point a, Point b) {return a.x * b.x + a.y * b.y;}
ftype norm(Point a) {return dot(a, a);}
ftype abs(Point a) {return sqrt(norm(a));}
ftype angle(Point a, Point b) {return acos(dot(a, b) / (abs(a) * abs(b)));}
ftype proj(Point a, Point b) {return dot(a, b) / abs(b);}
ftype cross(Point a, Point b) {return a.x * b.y - a.y * b.x;}
bool ccw(Point a, Point b, Point c) {return cross(b - a, c - a) > EPS;}
bool collinear(Point a, Point b, Point c) {return fabs(cross(b - a, c - a)) < EPS;}
Point intersect(Point a1, Point d1, Point a2, Point d2) {
    double t = cross(a2 - a1, d2) / cross(d1, d2);
    return a1 + d1 * t;
}