struct Vertex {
    int l, r;
    long long val, lazy;
    bool has_changed = false;
    Vertex() {}
    Vertex(int _l, int _r, long long _val, int _lazy = 0) : l(_l), r(_r), val(_val), lazy(_lazy) {}
};
struct PerSegmentTree {
    vector<Vertex> tree;
    vector<int> root;
    int build(const vector<int> &arr, int l, int r) {
        if (l == r) {
            tree.emplace_back(-1, -1, arr[l]);
            return tree.size() - 1;
        }
        int mid = (l + r) / 2;
        int left = build(arr, l, mid);
        int right = build(arr, mid + 1, r);
        tree.emplace_back(left, right, tree[left].val + tree[right].val);
        return tree.size() - 1;
    }  
    int add(int x, int l, int r, int u, int v, int amt) {
        if (l > v || r < u) return x;
        if (u <= l && r <= v) {
            tree.emplace_back(tree[x].l, tree[x].r, tree[x].val + 1LL * amt * (r - l + 1), tree[x].lazy + amt);
            tree.back().has_changed = true;
            return tree.size() - 1;
        }
        int mid = (l + r) >> 1;
        push(x, l, mid, r);
        int left = add(tree[x].l, l, mid, u, v, amt);
        int right = add(tree[x].r, mid + 1, r, u, v, amt);
        tree.emplace_back(left, right, tree[left].val + tree[right].val, 0);
        return tree.size() - 1;
    } 
    long long get_sum(int x, int l, int r, int u, int v) {
        if (r < u || l > v) return 0;
        if (u <= l && r <= v) return tree[x].val;
        int mid = (l + r) / 2;
        push(x, l, mid, r);
        return get_sum(tree[x].l, l, mid, u, v) + get_sum(tree[x].r, mid + 1, r, u, v);
    }
    void push(int x, int l, int mid, int r) {
        if (!tree[x].has_changed) return;
        Vertex left = tree[tree[x].l];
        Vertex right = tree[tree[x].r];
        tree.emplace_back(left);
        tree[x].l = tree.size() - 1;
        tree.emplace_back(right);
        tree[x].r = tree.size() - 1;

        tree[tree[x].l].val += tree[x].lazy * (mid - l + 1);
        tree[tree[x].l].lazy += tree[x].lazy;

        tree[tree[x].r].val += tree[x].lazy * (r - mid);
        tree[tree[x].r].lazy += tree[x].lazy;

        tree[tree[x].l].has_changed = true;
        tree[tree[x].r].has_changed = true;
        tree[x].lazy = 0;
        tree[x].has_changed = false;
    }
};
