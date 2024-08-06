struct Node {
    int val, prior, cnt;
    bool rev;
    Node *left, *right;
    Node() {}
    Node(int _val): val(_val), prior(rng()), cnt(1), rev(false), left(nullptr), right(nullptr) {}
};

int get_cnt(Node *n) { return n ? n->cnt : 0; }
void pull(Node *&n) {
    if (!n) return;
    n->cnt = get_cnt(n->left) + get_cnt(n->right) + 1;
}
void push(Node *treap) {
    if (!treap || !treap->rev) return;
    treap->rev = false;
    swap(treap->left, treap->right);
    if (treap->left) treap->left->rev ^= true;
    if (treap->right) treap->right->rev ^= true;
}
struct Treap {
    Node *root;
    bool implicit_key;
    Treap(bool _implicit_key = true): root(nullptr), implicit_key(_implicit_key) {}
    bool go_right(Node *treap, int pos_or_val) {
        if (implicit_key) {
            int local_idx = get_cnt(treap->left);
            return local_idx <= pos_or_val;
        }
        return treap->val <= pos_or_val;
    }
    pair<Node*, Node*> split(Node *treap, int pos_or_val) {
        // normal treap -> Left: all nodes having val <= val
        // implicit treap -> Left: all nodes having index <= pos
        if (!treap) return {};
        push(treap);
        if (go_right(treap, pos_or_val)) {
            if (implicit_key) pos_or_val -= (get_cnt(treap->left) + 1);
            auto pr = split(treap->right, pos_or_val);
            treap->right = pr.first;
            pull(treap);
            return {treap, pr.second};
        }
        else {
            auto pl = split(treap->left, pos_or_val);
            treap->left = pl.second;
            pull(treap);
            return {pl.first, treap};
        }
    }
    tuple<Node*, Node*, Node*> split(int u, int v) {
        auto [l, rem] = split(root, u - 1);
        auto [mid, r] = split(rem, v - (implicit_key ? u : 0));
        return {l, mid, r};
    }
    Node* merge(Node *l, Node *r) {
        push(l); push(r);
        if (!l || !r) return (l ? l : r);
        if (l->prior < r->prior) {
            l->right = merge(l->right, r);
            pull(l);
            return l;
        }
        else {
            r->left = merge(l, r->left);
            pull(r);
            return r;
        }
    }
    void insert(int pos, int val) {
        auto [l, r] = split(root, pos - 1);
        root = merge(merge(l, new Node(val)), r);
    }
    void insert(int val) {
        insert(val, val);
    }
    void erase(int u, int v) {
        auto [l, mid, r] = split(u, v);
        root = merge(l, r);
    }
    void reverse(int u, int v) {
        auto [l, mid, r] = split(u, v);
        mid->rev ^= true;
        root = merge(merge(l, mid), r);
    }
    int get_kth(Node *treap, int k) {
        if (!treap) return (int) 1e9;
        int sz = get_cnt(treap->left) + 1;
        if (sz == k) return treap->val;
        else if (sz < k) {
            return get_kth(treap->right, k - sz);
        }
        return get_kth(treap->left, k);
    }
};
