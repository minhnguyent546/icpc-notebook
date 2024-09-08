struct Node {
    int lc, rc;
    long long val, lazy;
    bool has_changed = false;
    Node() {}
    Node(int _lc, int _rc, long long _val, long long _lazy = 0):
        lc(_lc), rc(_rc), val(_val), lazy(_lazy) {}
};
struct PerSegmentTree {
    vector<Node> tree;
    int build(const vector<int> &arr, int l, int r) {
        if (l == r) {
            tree.emplace_back(-1, -1, arr[l]);
            return tree.size() - 1;
        }
        int mid = (l + r) / 2;
        int lc = build(arr, l, mid);
        int rc = build(arr, mid + 1, r);
        tree.emplace_back(lc, rc, tree[lc].val + tree[rc].val);
        return tree.size() - 1;
    }
    int add(int x, int l, int r, int u, int v, int amt) {
        if (l > v || r < u) return x;
        if (u <= l && r <= v) {
            tree.emplace_back(tree[x].lc, tree[x].rc, tree[x].val + 1LL * amt * (r - l + 1), tree[x].lazy + amt);
            tree.back().has_changed = true;
            return tree.size() - 1;
        }
        int mid = (l + r) >> 1;
        push(x, l, mid, r);
        int lc = add(tree[x].lc, l, mid, u, v, amt);
        int rc = add(tree[x].rc, mid + 1, r, u, v, amt);
        tree.emplace_back(lc, rc, tree[lc].val + tree[rc].val, 0);
        return tree.size() - 1;
    }
    long long get_sum(int x, int l, int r, int u, int v) {
        if (r < u || l > v) return 0;
        if (u <= l && r <= v) return tree[x].val;
        int mid = (l + r) / 2;
        push(x, l, mid, r);
        auto lhs = get_sum(tree[x].lc, l, mid, u, v);
        auto rhs = get_sum(tree[x].rc, mid + 1, r, u, v);
        return lhs + rhs;
    }
    void push(int x, int l, int mid, int r) {
        if (!tree[x].has_changed) return;
        Node left = tree[tree[x].lc];
        Node right = tree[tree[x].rc];
        tree.emplace_back(left);
        tree[x].lc = tree.size() - 1;
        tree.emplace_back(right);
        tree[x].rc = tree.size() - 1;

        tree[tree[x].lc].val += tree[x].lazy * (mid - l + 1);
        tree[tree[x].lc].lazy += tree[x].lazy;

        tree[tree[x].rc].val += tree[x].lazy * (r - mid);
        tree[tree[x].rc].lazy += tree[x].lazy;

        tree[tree[x].lc].has_changed = true;
        tree[tree[x].rc].has_changed = true;
        tree[x].lazy = 0;
        tree[x].has_changed = false;
    }
};
