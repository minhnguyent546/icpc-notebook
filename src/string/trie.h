struct Trie {
    const static int ALPHABET = 26;
    const static char minChar = 'a';
    struct Vertex {
        int next[ALPHABET];
        bool leaf;
        Vertex() {
            leaf = false;
            fill(next, next + ALPHABET, -1);
        }
    };
    vector<Vertex> trie;
    Trie() { trie.emplace_back(); }

    void insert(const string &s) {
        int i = 0;
        for (const char &ch : s) {
            int j = ch - minChar;
            if (trie[i].next[j] == -1) {
                trie[i].next[j] = trie.size();
                trie.emplace_back();
            }
            i = trie[i].next[j];
        }
        trie[i].leaf = true;
    }
    bool find(const string &s) {
        int i = 0;
        for (const char &ch : s) {
            int j = ch - minChar;
            if (trie[i].next[j] == -1) {
                return false;
            }
            i = trie[i].next[j];
        }   
        return (trie[i].leaf ? true : false);
    }
};