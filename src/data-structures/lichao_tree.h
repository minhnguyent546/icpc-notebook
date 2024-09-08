/**
 * Description: A segment tree that allows inserting a new line and querying
 * for minimum value over all lines at point x.
 * Usage: useful in convex hull trick.
 */

const long long INF_LL = (long long) 4e18;

struct Line {
    long long a, b;
    Line(long long _a = 0, long long _b = INF_LL): a(_a), b(_b) {}
    long long operator()(long long x) {
        return a * x + b;
    }
};

struct SegmentTree { // min query
    int n;
    vector<Line> tree;
    SegmentTree() {}
    SegmentTree(int _n): n(1) {
        while (n < _n) n *= 2;
        tree.resize(n * 2);
    }
    void insert(int x, int l, int r, Line line) {
        if (l == r) {
            if (line(l) < tree[x](l)) tree[x] = line;
            return;
        }
        int mid = (l + r) >> 1;
        bool b_left = line(l) < tree[x](l);
        bool b_mid = line(mid) < tree[x](mid);
        if (b_mid) swap(tree[x], line);
        if (b_left != b_mid) insert(x * 2, l, mid, line);
        else insert(x * 2 + 1, mid + 1, r, line);
    }
    long long query(int x, int l, int r, int at) {
        if (l == r) return tree[x](at);
        int mid = (l + r) >> 1;
        if (at <= mid) return min(tree[x](at), query(x * 2, l, mid, at));
        else return min(tree[x](at), query(x * 2 + 1, mid + 1, r, at));
    }
};
