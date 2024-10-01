/**
 * Description: a binary trie that supports inserting, erasing and querying
 * min/max $x \bitxor val$ for a given $x$.
 * Time: $O(BIT)$ per query
 * Status:
 *   - https://judge.yosupo.jp/problem/set_xor_min
 */

template<typename T, int BIT>
struct BinaryTrie {
    struct Node {
        array<int, 2> next;
        int cnt;
        Node(): cnt(0) {
            next.fill(-1);
        }
    };
    vector<Node> trie;
    BinaryTrie() { trie.emplace_back(); }
    bool contains(T val) {
        for (int j = BIT - 1, i = 0; j >= 0; --j) {
            int x = (val >> j) & 1;
            int ni = trie[i].next[x];
            if (ni == -1 || trie[ni].cnt == 0) return false;
            i = ni;
        }
        return true;
    }
    void insert(T val) {
        for (int j = BIT - 1, i = 0; j >= 0; --j) {
            int x = (val >> j) & 1;
            if (trie[i].next[x] == -1) {
                trie[i].next[x] = trie.size();
                trie.emplace_back();
            }
            i = trie[i].next[x];
            ++trie[i].cnt;
        }
    }
    void erase(T val) {
        for (int j = BIT - 1, i = 0; j >= 0; --j) {
            int x = (val >> j) & 1;
            int ni = trie[i].next[x];
            assert(ni != -1 && trie[ni].cnt > 0);
            i = ni;
            --trie[i].cnt;
        }
    }
    T get_min(T val) {
        T ret = 0;
        for (int j = BIT - 1, i = 0; j >= 0; --j) {
            int x = (val >> j) & 1;
            int l = trie[i].next[x];
            int r = trie[i].next[x ^ 1];
            if (l == -1 || trie[l].cnt == 0) {
                i = r;
                ret |= static_cast<T>(1) << j;
            } else {
                i = l;
            }
        }
        return ret;
    }
};
