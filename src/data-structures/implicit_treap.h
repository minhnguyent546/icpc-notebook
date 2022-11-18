struct Node {
    int val, prior, cnt;
    bool rev;
    Node *left, *right;
    Node() {}
    Node(int _val) : val(_val), prior(rng()), cnt(1), rev(false), left(nullptr), right(nullptr) {}
};
// Binary search tree + min-heap. 
struct Treap {
    Node *root;
    Treap() : root(nullptr) {}
    int get_cnt(Node *n) { return n ? n->cnt : 0; }
    void upd_cnt(Node *&n) {
        if (n) n->cnt = get_cnt(n->left) + get_cnt(n->right) + 1;
    }
    void push_rev(Node *treap) {
        if (!treap || !treap->rev) return;
        treap->rev = false;
        swap(treap->left, treap->right);
        if (treap->left) treap->left->rev ^= true;
        if (treap->right) treap->right->rev ^= true;
    }
    pair<Node*, Node*> split(Node *treap, int x, int smaller = 0) {
        if (!treap) return {};
        push_rev(treap);
        int idx = smaller + get_cnt(treap->left); // implicit val.
        if (idx <= x) {
            auto pr = split(treap->right, x, idx + 1);
            treap->right = pr.first;
            upd_cnt(treap);
            return {treap, pr.second};
        }
        else {
            auto pl = split(treap->left, x, smaller);
            treap->left = pl.second;
            upd_cnt(treap);
            return {pl.first, treap};
        }
    }
    Node* merge(Node *l, Node *r) {
        push_rev(l); push_rev(r);
        if (!l || !r) return (l ? l : r);
        if (l->prior < r->prior) {
            l->right = merge(l->right, r);
            upd_cnt(l);
            return l;
        }
        else {
            r->left = merge(l, r->left);
            upd_cnt(r);
            return r;
        }
    }
    void insert(int pos, int val) {
        if (!root) {
            root = new Node(val);
            return;
        }
        Node *l, *m, *r;
        m = new Node(val);
        tie(l, r) = split(root, pos - 1);
        root = merge(l, merge(m, r));
    }
    void erase(int pos_l, int pos_r) {
        Node *l, *m, *r;
        tie(l, r) = split(root, pos_l - 1);
        tie(m, r) = split(r, pos_r - pos_l);
        root = merge(l, r);
    }
    void reverse(int pos_l, int pos_r) {
        Node *l, *m, *r;
        tie(l, r) = split(root, pos_l - 1);
        tie(m, r) = split(r, pos_r - pos_l);
        m->rev ^= true;
        root = merge(l, merge(m, r));
    }
    int query(int pos_l, int pos_r);
         // returns answer for corresponding types of query.
    void inorder(Node *n) {
        if (!n) return;
        push_rev(n);
        inorder(n->left);
        cout << n->val << ' ';
        inorder(n->right);
    }
    void print() {
        inorder(root);
        cout << '\n';
    }
};