struct Vertex {
    int next[30];
    int output;
    int link;
    Vertex() {
        fill(begin(next), end(next), 0);
        output = 0;
        link = 0;
    }
};

vector<Vertex> trie(1);

void add_edge(string s) {
    int u = 0;
    for (auto c : s) {
        if (trie[u].next[c - 'a'] == 0) {
            trie[u].next[c - 'a'] = trie.size();
            trie.emplace_back();
        }
        u = trie[u].next[c - 'a'];
    }
    trie[u].output++;
}

void get_link() {
    int s = 0;
    queue<int> q;
    for (int i = 0; i < 26; i++) {
        if (trie[s].next[i] != 0) {
            q.push(trie[s].next[i]);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < 26; i++) {
            if (trie[u].next[i]) {
                trie[trie[u].next[i]].link = trie[trie[u].link].next[i];
                q.push(trie[u].next[i]);
            }
            else {
                trie[u].next[i] = trie[trie[u].link].next[i];
            }
        }
    }
}
