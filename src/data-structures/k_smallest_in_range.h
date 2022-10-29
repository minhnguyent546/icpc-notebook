struct Vertex {
    int l, r;
    int sum;
    Vertex() {}
    Vertex(int _l, int _r, int _sum) : l(_l), r(_r), sum(_sum) {}
};
struct PerSegmentTree {
    int n;
    vector<Vertex> tree;
    vector<int> root; // id of root for each version. 
    PerSegmentTree(int _n) : n(_n)  {}
    int build(int l, int r, int v = 0) {
        if (l == r) {
            tree.emplace_back(-1, -1, v);
            return tree.size() - 1;
        }
        int mid = (l + r) >> 1;
        int left = build(l, mid);
        int right = build(mid + 1, r);
        tree.emplace_back(left, right, tree[left].sum + tree[right].sum);
        return tree.size() - 1;
    }
    int add(int x, int l, int r, int pos, int val) {
        if (l == r) {
            tree.emplace_back(-1, -1, tree[x].sum + val);
            return tree.size() - 1;
        }
        int mid = (l + r) >> 1;
        int left = tree[x].l, right = tree[x].r;
        if (pos <= mid) {   
            left = add(left, l, mid, pos, val);
        }
        else {
            right = add(right, mid + 1, r, pos, val);
        }
        tree.emplace_back(left, right, tree[left].sum + tree[right].sum);
        return tree.size() - 1;
    }
    int k_th_smallest(int prev, int cur, int l, int r, int k) {
        if (l == r) return l;
        int cnt_left = tree[tree[cur].l].sum - tree[tree[prev].l].sum;
        int mid = l + (r - l) / 2;
        if (cnt_left >= k) {
            return k_th_smallest(tree[prev].l, tree[cur].l, l, mid, k);
        }
        else {
            return k_th_smallest(tree[prev].r, tree[cur].r, mid + 1, r, k - cnt_left);
        }
    }
};