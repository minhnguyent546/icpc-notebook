using tree_type = long long;
struct FenwickTree {
    int n;
    vector<tree_type> fenw_coeff, fenw;
    FenwickTree() {}
    FenwickTree(int _n) : n(_n) {
        fenw_coeff.assign(n, 0); // fenwick tree with coefficient (n - i).
        fenw.assign(n, 0); // normal fenwick tree.
    }
    void build(const vector<int> &A) {
        assert((int) A.size() == n);
        vector<int> diff(n);
        diff[0] = A[0];
        for (int i = 1; i < n; ++i) {
            diff[i] = A[i] - A[i - 1];
        }
        fenw_coeff[0] = (long long) diff[0] * n;
        fenw[0] = diff[0];
        for (int i = 1; i < n; ++i) {
            fenw_coeff[i] = fenw_coeff[i - 1] + (long long) diff[i] * (n - i);
            fenw[i] = fenw[i - 1] + diff[i];
        }
        for (int i = n - 1; i >= 0; --i) {
            int j = (i & (i + 1)) - 1;
            if (j >= 0) {
                fenw_coeff[i] -= fenw_coeff[j];
                fenw[i] -= fenw[j];
            }
        }
    }
    void add(vector<tree_type> &fenw, int i, tree_type val) {
        while (i < n) {
            fenw[i] += val;
            i |= (i + 1);
        }
    }
    tree_type __prefix_sum(vector<tree_type> &fenw, int i) {
        tree_type res{};
        while (i >= 0) {
            res += fenw[i];
            i = (i & (i + 1)) - 1;
        }
        return res;
    }
    tree_type prefix_sum(int i) {
        return __prefix_sum(fenw_coeff, i) - __prefix_sum(fenw, i) * (n - i - 1);
    }
    void range_add(int l, int r, tree_type val) {
        add(fenw_coeff, l, (n - l) * val);
        add(fenw_coeff, r + 1, (n - r - 1) * (-val));
        add(fenw, l, val);
        add(fenw, r + 1, -val);
    }
    tree_type range_sum(int l, int r) {
        return prefix_sum(r) - prefix_sum(l - 1);
    }
};