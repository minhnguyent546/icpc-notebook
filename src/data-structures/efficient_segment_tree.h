template<typename T> struct SegmentTree {
    int n;
    vector<T> tree;
    SegmentTree(int _n) : n(_n), tree(2 * n) {}
    T merge(const T &left, const T &right) {
        return left + right;
    }
    template<typename G> 
    void build(const vector<G> &initial) {
        assert((int) initial.size() == n);
        for (int i = 0; i < n; ++i) {
            tree[i + n] = initial[i];
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = merge(tree[i * 2], tree[i * 2 + 1]);
        }
    }
    void modify(int i, int v) {
        tree[i += n] = v;
        for (i /= 2; i > 0; i /= 2) {
            tree[i] = merge(tree[i * 2], tree[i * 2 + 1]);
        }
    }
    T get_sum(int l, int r) {
        // sum of elements from l to r - 1.
        T ret{};
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) ret = merge(ret, tree[l++]);
            if (r & 1) ret = merge(ret, tree[--r]);
        }
        return ret;
    }
};
