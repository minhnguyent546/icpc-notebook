/**
 * Description: A segment tree with range updates and sum queries that supports three types of operations: 
 *  + Increase each value in range [l, r] by x (i.e. a[i] += x).
 *  + Set each value in range [l, r] to x (i.e. a[i] = x).
 *  + Determine the sum of values in range [l, r].  
 */

struct SegmentTree {
    int n;
    vector<long long> tree, lazy_add, lazy_set;
    SegmentTree(int _n) : n(_n) {
        int p = 1;
        while (p < n) p *= 2;
        tree.resize(p * 2);
        lazy_add.resize(p * 2);
        lazy_set.resize(p * 2);
    }
    long long merge(const long long &left, const long long &right) {
        return left + right;
    }
    void build(int id, int l, int r, const vector<int> &arr) {
        if (l == r) {
            tree[id] += arr[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(id * 2, l, mid, arr);
        build(id * 2 + 1, mid + 1, r, arr);
        tree[id] = merge(tree[id * 2], tree[id * 2 + 1]);
    }
    void push(int id, int l, int r) {
        if (lazy_set[id] == 0 && lazy_add[id] == 0) return;
        int mid = (l + r) >> 1;
        for (int child : {id * 2, id * 2 + 1}) {
            int range = (child == id * 2 ? mid - l + 1 : r - mid);
            if (lazy_set[id] != 0) {
                lazy_add[child] = 0;
                lazy_set[child] = lazy_set[id];
                tree[child] = range * lazy_set[id];
            }
            lazy_add[child] += lazy_add[id];
            tree[child] += range * lazy_add[id];
        }
        lazy_add[id] = lazy_set[id] = 0;

    }
    void update(int id, int l, int r, int u, int v, int amount, bool set_value = false) {
        if (r < u || l > v) return;
        if (u <= l && r <= v) {
            if (set_value) {
                tree[id] = 1LL * amount * (r - l + 1);
                lazy_set[id] = amount;
                lazy_add[id] = 0; // clear all previous updates. 
            }
            else {
                tree[id] += 1LL * amount * (r - l + 1);
                lazy_add[id] += amount;
            }
            return;
        }
        push(id, l, r);
        int mid = (l + r) >> 1;
        update(id * 2, l, mid, u, v, amount, set_value);
        update(id * 2 + 1, mid + 1, r, u, v, amount, set_value);
        tree[id] = merge(tree[id * 2], tree[id * 2 + 1]);
    }
    long long get(int id, int l, int r, int u, int v) {
        if (r < u || l > v) return 0;
        if (u <= l && r <= v) {
            return tree[id];
        }
        push(id, l, r);
        int mid = (l + r) >> 1;
        long long left = get(id * 2, l, mid, u, v);
        long long right = get(id * 2 + 1, mid + 1, r, u, v);
        return merge(left, right);
    }
};