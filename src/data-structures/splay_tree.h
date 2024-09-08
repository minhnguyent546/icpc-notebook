/**
 * Description: a type of self-balancing binary search tree,
 * when a node is accessed, a splay operation is performed on that node to make
 * it become the root of the tree.
 * Time: amortized time complexity is $O(\log{N})$.
 */

struct Node {
    int val, cnt;
    bool rev;
    Node *left, *right, *par;
    Node() {}
    Node(int _val = 0):
        val(_val), cnt(1), rev(false),
        left(nullptr), right(nullptr), par(nullptr) {}
    friend int get_cnt(Node *n) { return n ? n->cnt : 0; }
    void pull() {
        cnt = get_cnt(left) + 1 + get_cnt(right);
        if (left) left->par = this;
        if (right) right->par = this;
    }
    void push() {
        if (!rev) return;
        rev = false;
        swap(left, right);
        if (left) left->rev ^= 1;
        if (right) right->rev ^= 1;
    }
};
bool is_root(Node *n) {
    return (n != nullptr && n->par == nullptr);
}
struct SplayTree {
    void splay(Node *u) {
        if (u == nullptr) return;
        u->push();
        while (!is_root(u)) {
            Node *par = u->par;
            if (!is_root(par)) {
                if ((par->left == u) == (par->par->left == par)) {
                    // zig-zig
                    rotate(par);
                } else {
                    // zig-zag
                    rotate(u);
                }
            }
            rotate(u);
        }
        u->pull();
    }
    Node* merge(Node *u, Node *v) {
        if (!u) return v;
        if (!v) return u;
        while (true) {
            u->push();
            Node *next = u->right;
            if (next == nullptr) break;
            u = next;
        }
        splay(u); splay(v);
        assert(u->right == nullptr);
        u->right = v;
        u->pull();
        return u;
    }
    void rotate(Node *u) {
        Node *par = u->par;
        assert(par != nullptr);
        par->push(); u->push();
        u->par = par->par;
        if (par->par != nullptr) {
            if (u->par->left == par) {
                u->par->left = u;
            } else {
                u->par->right = u;
            }
        }
        if (par->left == u) {
            par->left = u->right;
            u->right = par;
        } else {
            par->right = u->left;
            u->left = par;
        }
        par->pull(); u->pull();
    }
    Node* node_at_index(Node *n, int pos) {
        if (pos < 0 || pos >= get_cnt(n)) return nullptr;
        n->push();
        int idx = get_cnt(n->left);
        if (idx == pos) return n;
        else if (idx < pos) {
            return node_at_index(n->right, pos - idx - 1);
        } else {
            return node_at_index(n->left, pos);
        }
    }
    pair<Node*, Node*> split(Node *n, int pos) {
        if (pos < 0) return {nullptr, n};
        if (pos >= get_cnt(n) - 1) return {n, nullptr};
        Node *l = node_at_index(n, pos);
        splay(l);
        Node *r = l->right;
        l->right = nullptr;
        r->par = nullptr;
        l->pull();
        return {l, r};
    }
    tuple<Node*, Node*, Node*> split(Node *n, int u, int v) {
        auto [l, rem] = split(n, u - 1);
        auto [mid, r] = split(rem, v - u);
        return {l, mid, r};
    }
    Node* reverse(Node *n, int u, int v) {
        auto [l, mid, r] = split(n, u, v);
        mid->rev ^= 1;
        Node *ret = merge(l, merge(mid, r));
        return ret;
    }
    Node* insert(Node *n, int pos, int val) {
        auto [l, r] = split(n, pos - 1);
        return merge(l, merge(new Node(val), r));
    }
    Node* erase(Node *n) {
        if (!n) return nullptr;
        splay(n);
        Node *left = n->left, *right = n->right;
        n->left = n->right = nullptr;
        if (left) left->par = nullptr;
        if (right) right->par = nullptr;

        Node *ret = merge(left, right);
        if (ret != nullptr) {
            ret->par = n->par;
        }
        return ret;
    }
};
