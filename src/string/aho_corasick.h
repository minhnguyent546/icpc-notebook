struct Vertex {
    int next[30];
    int output;
    int link;
    int ed, st;

    Vertex() {
        fill(begin(next), end(next), 0);
        output = link = 0;
        ed = st = 0;
    }
};

const int maxn = 1e5 + 3;
vector<Vertex> trie(1);
vector<int> adj[maxn];
int back[maxn], pre[maxn], val[maxn], vs[maxn];
map<string, int> mp;
string str[maxn];
int n;

void add_edge(string s, int idx) {
    int u = 0;

    for (auto j : s) {
        if (trie[u].next[j - 'a'] == 0) {
            trie[u].next[j - 'a'] = trie.size();
            trie.emplace_back();
        }
        u = trie[u].next[j - 'a'];
    }
    trie[u].output++;
    if (trie[u].st == 0)
        trie[u].st = idx;

    back[idx] = trie[u].ed;
    trie[u].ed = idx;
}

void get_link() {
    int u = 0;
    queue<int> q;

    for (int i = 0; i < 26; i++) {
        if (trie[u].next[i] != 0)
            q.push(trie[u].next[i]);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < 26; i++) {
            int v = trie[u].next[i];
            if (v != 0) {
                trie[v].link = trie[trie[u].link].next[i];
                int y = trie[v].link;
                if (trie[v].ed == 0) {
                    trie[v].ed = trie[y].ed;
                }
                else {
                    back[trie[v].ed] = trie[y].ed;
                }
                q.push(v);
            }
            else {
                trie[u].next[i] = trie[trie[u].link].next[i];
            }
        }
    }

    for (int i = 1; i <= n; i++)
        adj[back[i]].push_back(i);
}
