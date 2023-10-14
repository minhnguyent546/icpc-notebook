const int nmax = (int)2e5 + 1;
vector<int> adj[nmax];
int sz[nmax]; // sz[u] is the size of the subtree rooted at u
bool big[nmax];

void add(int u, int p, int del) {
    // do something...
    for(int v : adj[u]) {
        if(big[v] == false) {
            add(v, u, del);
        }
    }
}

void dsuOnTree(int u, int p, int keep) {
    int bigC = -1;
    for(int v : adj[u]) {
        if(v != p && (bigC == -1 || sz[bigC] < sz[v])) {
            bigC = v;
        }
    }
    for(int v : adj[u]) {
        if(v != p && v != bigC) dsuOnTree(v, u, 0);
    }
    if(bigC != -1) {
        big[bigC] = true;
        dsuOnTree(bigC, u, 1);
    }
    add(u, p, 1);
    if(bigC != -1) big[bigC] = false;
    if(keep == 0) add(u, p, -1);
}