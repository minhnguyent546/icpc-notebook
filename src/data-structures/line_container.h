/**
 *  Source: kactl
 *  Description: container that allow you can add lines in form `ax + b` and query maximum value at `x`.
 **/
using num_t = int;
struct Line {
    num_t a, b; // ax + b
    mutable num_t x; // x-intersect with the next line in the hull
    bool operator<(const Line &other) const {
        return a < other.a;
    }
    bool operator<(num_t other_x) const {
        return x < other_x;
    }
};

struct LineContainer : multiset<Line, less<>> { // max-query
    // for doubles, use INF = 1 / 0.0
    static const num_t INF = numeric_limits<num_t>::max();

    num_t floor_div(num_t a, num_t b) {
        return a / b - ((a ^ b) < 0 && a % b != 0);
    }
    bool isect(iterator u, iterator v) {
        if (v == end()) {
            u->x = INF;
            return false;
        }
        if (u->a == v->a) u->x = (u->b > v->b ? INF : -INF);
        else u->x = floor_div(v->b - u->b, u->a - v->a);
        return u->x >= v->x;
    }
    void add(num_t a, num_t b) {
        auto z = insert({a, b, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) {
            y = erase(y);
            isect(x, y);
        }
        while ((y = x) != begin() && (--x)->x >= y->x) {
            isect(x, erase(y));
        }
    }
    num_t query(num_t x) {
        assert(!empty());
        auto it = *lower_bound(x);
        return it.a * x + it.b;
    }
};