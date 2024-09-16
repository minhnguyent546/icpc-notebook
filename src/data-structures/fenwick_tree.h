/**
 * Description: a minimal and simple data structure for point update and range query
 * Note:
 * - For range update and point query, create a Fenwick tree on array $D$ defined by $D_0 = A_0, D_i = A_i - A_{i - 1}$
 * - For range update and range query, the idea is the same as above, but we can calculate the prefix as follow: $\sum\limits_{i = 0}^{k}{A_i} = \sum\limits_{i = 0}^{k}{\sum\limits_{j = 0}^{i}{D_j}} = (k + 1)\sum\limits_{i = 0}^{k}{D_i} - \sum\limits_{i = 0}^{k}{iD_i}$, thus we can maintain two prefix sums, $D_i$ and $iD_i$, with two Fenwick trees.
 * Time: $O(\log{N})$
 */

template<typename T>
struct Fenwick {
    int n;
    vector<T> tree;
    Fenwick() {}
    Fenwick(int _n): n(_n), tree(n) {}
    void add(int i, T val) {
        while (i < n) {
            tree[i] += val;
            i |= (i + 1);
        }
    }
    T pref(int i) {
        T res{};
        while (i >= 0) {
            res += tree[i];
            i = (i & (i + 1)) - 1;
        }
        return res;
    }
    T query(int l, int r) {
        return pref(r) - pref(l - 1);
    }
    int lower_bound(T val) {
        int x = 0;
        T s{};
        for (int i = 1 << __lg(n); i > 0; i /= 2) {
            if (i + x - 1 < n && s + tree[x + i - 1] < val) {
                s += tree[x + i - 1];
                x += i;
            }
        }
        return x;
    }
};
